/**
    httpRequest.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#include "httpRequest.h"

HTTPRequest::HTTPRequest() {
	sent = false;
	revd = false;
}

HTTPRequest::~HTTPRequest() {

}

bool HTTPRequest::makeSocket() {
    _msock = socket(AF_INET, SOCK_STREAM, 0);
    //Failed?
    if(!IsValid()) {
        return false;
    }
    int on = 1;
    if(::setsockopt(_msock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)) == -1) {
        return false;
    }
    return true;
}

bool HTTPRequest::sendGETRequest(string url, string remainingAddr) {
	sent = false;
	revd = false;
	
	if(_msock != -1) {
		//Close existing connection, let's not get interrupted here!
		::close(_msock);
	}
	if(_msock == -1) { 
		do {
			makeSocket();
		}while(_msock == -1);
	}
	//Pre-connect event
	struct hostent *host = ::gethostbyname(url);
	if(host == null || host->h_addr == NULL) {
		cout << "HTTPRequest::sendGETRequest(): Invalid host." << endl;
		return false;
	}
	bzero(&_maddr, sizeof(_maddr));
	_maddr.sin_family = AF_INET;
	_maddr.sin_port = htons(_HTTP_PORT);
	memcpy(&_maddr.sin_addr, host->h_addr, host->h_length);
	//Connect...
	if(::connect(sock, (struct sockaddr *)&_maddr, sizeof(_maddr)) < 0) {
		::close(_msock);
		cout << "HTTPRequest::sendGETRequest(): Cannot connect." << endl;
		return false;
	}
	//Prepare GET request for server.
	request = "";
	request += "GET " + remainingAddr + " HTTP/1.1\r\n";
	request += "Host: " + url + "\r\n";
	request += "Connection: Close\r\n";
	request += "\r\n\r\n";
	//Send the request
	if(::send(_msock, request.c_str(), request.length(), 0) != (int)request.length()) {
		cout << "HTTPRequest::sendGETRequest(): Something went wrong in the send buffer." << endl;
		return false;
	}	
	sent = true;
	//Recieve
	while(::read(_msock, &sendBuffer, _SEND_BUFFER_SIZE) > 0) {
		response += sendBuffer;
	}
	revd = true;
	return true;
}
