/**
    httpRequest.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

/*
#ifndef _HTTPREQUEST_H
#define _HTTPREQUEST_H

#define _HTTP_PORT 80
#define _SEND_BUFFER_SIZE 1024

class HTTPRequest {
    public:
    	HTTPRequest();
    	~HTTPRequest();
    	
    	bool makeSocket();
    	
    	bool sendGETRequest(string url, string remainingAddr);
    	//bool sendPOSTRequest(string address, string payload);
    	
    	bool sendComplete() { return sent; }
    	bool responseComplete() { return revd; }
    	
    	const string payload() { return request; }
    	const string received() { return response; }
    	
    private:
    	ACHAR sendBuffer[_SEND_BUFFER_SIZE];
    	string request;
    	string response;

        S32 _msock;  
        sockaddr_in _maddr;    	
        
        bool sent;
        bool revd;
};

#endif //_HTTPREQUEST_H

*/