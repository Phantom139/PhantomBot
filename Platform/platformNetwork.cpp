/**
	platformNetwork.cpp
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "../include.h"

Network::Network() : initd(false) {

}

Network::~Network() {

}

void Network::init() {
	if (!initd) {
		initd = true;
	}
}

void Network::tick() {
	//Update all sockets...
	if (!socketList.size()) {
		return;
	}

	S32 optVal;
	S32 optLen;
	S32 bytesRead;
	bool closeSocket = false;

	for (SIZE_T i = 0; i < socketList.size(); i++) {
		//Initial Tests
		Socket *s = socketList[i];
		if (!s->isValidSocket()) {
			//Closed, Remove it.
			socketList.erase(socketList.begin() + i);
			continue;
		}
		//Run Socket Events...
		switch (s->fetchState()) {
			case SocketStatus::StateInvalid:
				cout << "Network::tick(): Invalid Socket State in list, breaking..." << endl;
				break;

			case SocketStatus::StatePending:
				//Any updates?
				if (getsockopt(s->get(), SOL_SOCKET, SO_ERROR, (ACHAR *)&optVal, &optLen)) {
					cout << "Network::tick(): Socket in slot " << i << " unable to access options, killing." << endl;
					closeSocket = true;
				}
				else {
					if (optVal == EINPROGRESS) {
						//We're still waiting.
						break;
					}
					else if (optVal == 0) {
						//We're connected!
						s->setState(SocketStatus::StateConnected);
					}
				}
				break;

			case SocketStatus::StateConnected:
				bytesRead = 0;
				SocketCode rc = s->receive(s->getBuffer(), _MAXRECV, &bytesRead);
				if (rc == SocketCode::Disconnected) {
					cout << "Server disconnected the socket object." << endl;
					s->onServerDisconect();
					closeSocket = true;
				}
				else if (rc == SocketCode::NoError) {
					if (bytesRead > 0) {
						s->onResponse(s->getBuffer());
					}
					else {
						if (bytesRead < 0) {
							cout << "Socket " << i << " Triggered <0 Read Error. Errno: " << errno << endl;
						}
						//Trigger End-Of-Buffer
						s->onResponseRN();
						if (s->fetchStyle() == SocketStyle::Socket_OneAndDone) {
							//We're done, DC.
							closeSocket = true;
						}
					}
				}
				else if (rc == SocketCode::Timeout) {
					//Nothingto see here folks...
				}
				else {
					//Error..
					cout << "An error occured on socket " << i << " errno: " << errno << endl;
					closeSocket = true;
				}
				break;
		}
		if (closeSocket) {
			s->close();
		}
	}
}

void Network::addSocket(Socket *s) {
	socketList.push_back(s);
}

Network &Network::fetchInstance() {
	if (managedSingleton<Network>::instance() == NULL) {
		managedSingleton<Network>::createInstance();
	}
	return *(managedSingleton<Network>::instance());
}