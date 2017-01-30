/**
	windowsSocket.cpp
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "../../include.h"

Socket::Socket() : sObj(NULL) {

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
		cout << "Socket::create(): Failed to create socket, INVALID_SOCKET code thrown. (" << WSAGetLastError() << ")" << endl;
		return false;
	}
	//Try to init.
	S32 on = 1;
	if(setsockopt(sObj, SOL_SOCKET, SO_REUSEADDR, (UFC32)&on, sizeof(on)) == -1) {
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

GeneralSocket::SocketReturnCode Socket::connect(UFC32 host, const U32 port) {
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
		return Connected;
	}
	cout << "Socket::connect(): Failed to connect: " << status << ", errno " << errno << endl;
	return ConnectionFailed;
}