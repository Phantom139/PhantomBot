/**
	windowsSocket.cpp
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "../../include.h"
#ifdef PHANTOMBOT_WINDOWS

	Socket::Socket() : sObj(INVALID_SOCKET) {
		inBuff = new ACHAR[_MAXRECV];
	}

	Socket::~Socket() {

	}

	bool Socket::create() {
		WSAData wsa;
		int wsaResult;

		wsaResult = WSAStartup(MAKEWORD(2, 2), &wsa);
		if (wsaResult != 0) {
			cout << "Socket::create(): Failed to initialize WSA object (WSA Error: " << wsaResult << ")" << endl;
			return false;
		}
		sObj = socket(AF_INET, SOCK_STREAM, 0);
		if (sObj == INVALID_SOCKET) {
			WSACleanup();
			cout << "Socket::create(): Failed to create socket, INVALID_SOCKET code thrown. (" << WSAGetLastError() << ")" << endl;
			return false;
		}
		//Try to init.
		S32 on = 1;
		if(setsockopt(sObj, SOL_SOCKET, SO_REUSEADDR, (UFC32)&on, sizeof(on)) == -1) {
			WSACleanup();
			cout << "Socket::create(): Failed to initialize socket." << endl;
			return false;
		}
		//Good!
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
		S32 retCode = ::closesocket(sObj);
		sObj = INVALID_SOCKET;
		WSACleanup();
		return retCode == 0;
	}

	bool Socket::shutdown() {
		if (!isValidSocket()) {
			return false;
		}
		S32 retCode = ::shutdown(sObj, SD_SEND);
		if (retCode == SOCKET_ERROR) {
			cout << "Socket::shutdown(): Failed to shut down socket: " << WSAGetLastError() << endl;
			::closesocket(sObj);
			sObj = INVALID_SOCKET;
			WSACleanup();
			return false;
		}
		onSelfDisconnect();
		return true;
	}

	bool Socket::send(UFC32 message) const {
		if (!isValidSocket()) {
			return false;
		}
		S32 sRet = ::send(sObj, message, strlen(message), 0);
		if (sRet == -1) {
			cout << "Socket::send(): Failed to send message: " << WSAGetLastError() << endl;
			return false;
		}
		return true;
	}

	SocketCode Socket::receive(ACHAR *buffer, S32 bufferSize, S32 *bytesRead) const {
		memset(inBuff, NULL, sizeof(inBuff));
		*bytesRead = ::recv(sObj, (ACHAR *)inBuff, bufferSize, 0);
		strcpy(buffer, inBuff);
		//
		switch (*bytesRead) {
			case -1:
				if(WSAGetLastError() == WSAETIMEDOUT || WSAGetLastError() == WSAEWOULDBLOCK) {
					return Timeout;
				}
				else {
					cout << "Socket::Recieve() Status: -1: " << WSAGetLastError() << "\n";
					return RecieveError;
				}

			case 0:
				cout << "Socket::Recieve(): Server issued disconnect command.\n";
				//onServerDisconect(); //TO-Do: Fix const Socket error...
				return Disconnected;
		}
		return NoError;
	}

	void Socket::setNonBlocking(const bool status) {
		UL block = status;
		S32 opt = ioctlsocket(sObj, FIONBIO, &block);
		if (opt) {
			cout << "Socket::setNonBlocking(): Failed with error " << WSAGetLastError() << endl;
		}
	}

	bool Socket::isValidSocket() const {
		return sObj != INVALID_SOCKET;
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
