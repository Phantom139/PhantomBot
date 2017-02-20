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

			case SocketStatus::StateConnected:

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