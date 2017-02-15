/**
    tcpRequest.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/


#include "tcpRequest.h"

TCPRequest::TCPRequest() {
	sObj = new Socket();
}

TCPRequest::~TCPRequest() {
	if (sObj->isValidSocket()) {
		sObj->close();
	}
}