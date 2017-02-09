/**
	linuxSocket.cpp
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "../../include.h"
#ifdef PHANTOMBOT_LINUX

	Socket::Socket() : sObj(-1) {

	}

	Socket::~Socket() {

	}

	bool Socket::create() {
		sObj = socket(AF_INET, SOCK_STREAM, 0);
		//Failed?
		if (!isValidSocket()) {
			return false;
		}
		//Init the Socket
		S32 on = 1;
		if (setsockopt(sObj, SOL_SOCKET, SO_REUSEADDR, (UFC32)&on, sizeof(on)) == -1) {
			//Init failed
			return false;
		}
		//Done!
		return true;
	}

	bool Socket::bind(const U32 port) {
		if (!isValidSocket()) {
			return false;
		}
		_mAddr.sin_family = AF_INET;
		_mAddr.sin_addr.s_addr = INADDR_ANY;
		_mAddr.sin_port = htons(port);
		//Bind the port
		S32 bRet = ::bind(sObj, (struct sockaddr *)&_mAddr, sizeof(_mAddr));
		if (bRet == -1) {
			return false;
		}
		return true;
	}

	bool Socket::listen() const {
		if (!isValidSocket()) {
			return false;
		}
		S32 lRet = ::listen(sObj, _MAXCONNECTIONS);
		if (lRet == -1) {
			return false;
		}
		return true;
	}

	bool Socket::accept(Socket &s) {
		S32 aLen = sizeof(_mAddr);
		s.sObj = ::accept(sObj, (sockaddr *)&_mAddr, (socklen_t *)&aLen);
		if (s.sObj <= 0) {
			return false;
		}
		return true;
	}

	SocketCode Socket::connect(UFC32 host, const U32 port) {
		if (!isValidSocket()) {
			return InvalidSocket;
		}
		struct hostent *he;
		if ((he = gethostbyname(host)) == NULL) {
			cout << "Socket::connect(): Failed to convert " << host << " to an IP" << endl;
		}
		_mAddr.sin_family = AF_INET;
		_mAddr.sin_port = htons(port);
		memcpy(&_mAddr.sin_addr, he->h_addr_list[0], he->h_length);
		S32 status = ::connect(sObj, (sockaddr *)&_mAddr, sizeof(_mAddr));
		if (status == 0) {
			onConnected();
			return Connected;
		}
		cout << "Socket::connect(): Failed to connect: " << status << ", errno " << errno << endl;
		onConnectFailed();
		return ConnectionFailed;
	}

	bool Socket::close() {
		if (!isValidSocket()) {
			return false;
		}
		onSelfDisconnect();
		S32 retCode = ::close(sObj);
		sObj = -1;
		return retCode == 0;
	}

	bool Socket::shutdown() {
		if (!isValidSocket()) {
			return false;
		}
		S32 retCode = ::shutdown(sObj, SHUT_RDWR);
		if (retCode != 0) {
			cout << "Socket::shutdown(): Failed to shut down socket: " << errno << endl;
			::close(sObj);
			sObj = -1;
			return false;
		}
		onSelfDisconnect();
		return true;
	}

	bool Socket::send(UFC32 message) const {
		if (!isValidSocket()) {
			return false;
		}
		S32 sRet = ::send(sObj, message, strlen(message), MSG_NOSIGNAL);
		if (sRet == -1) {
			return false;
		}
		return true;
	}

	SocketCode Socket::receive(U8 *buffer, S32 bufferSize, S32 *bytesRead) const {
		*bytesRead = ::recv(sObj, (ACHAR *)buffer, bufferSize, 0);
		switch (*bytesRead) {
			case -1:
				if(errno != 11) {
					cout << "Socket::Recieve() Status: -1: " << errno << "\n";
					return RecieveError;
				}
				else {
					return Timeout;
				}

			case 0:
				cout << "Socket::Recieve(): Server issued disconnect command.\n";
				//onServerDisconect(); //TO-Do: Fix const Socket error...
				return Disconnected;
		}
		return NoError;
	}

	void Socket::setNonBlocking(const bool status) {
		S32 options;
		options = fcntl(sObj, F_GETFL);
		if (options < 0) {
			return;
		}
		if (status) {
			options = (options | O_NONBLOCK);
		}
		else {
			options = (options & ~O_NONBLOCK);
		}
		fcntl(sObj, F_SETFL, options);
	}

	bool Socket::isValidSocket() const {
		return sObj != -1;
	}

	void Socket::onConnected() {

	}

	void Socket::onConnectFailed() {

	}

	void Socket::onSelfDisconnect() {

	}

	void Socket::onServerDisconect() {

	}

#endif
