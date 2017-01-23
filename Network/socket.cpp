/**
    socket.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "socket.h"

Socket::Socket() : _msock(-1) {
    memset(&_maddr, 0, sizeof(_maddr));
    socketBuffer = new char[_MAXRECV];
}

Socket::~Socket() {
    if(IsValid()) {
        ::close(_msock);
    }
}

bool Socket::Create() {
    _msock = socket(AF_INET, SOCK_STREAM, 0);
    //Failed?
    if(!IsValid()) {
        return false;
    }
    //Init the Socket
    int on = 1;
    if(setsockopt(_msock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)) == -1) {
        //Init failed
        return false;
    }
    //Done!
    return true;
}

bool Socket::Bind(const unsigned int port) {
    if(!IsValid()) {
        return false;
    }
    //UNIX has a set of pre-commands it wants done for the _maddr object instance, do so now.
    _maddr.sin_family = AF_INET;
    _maddr.sin_addr.s_addr = INADDR_ANY;
    _maddr.sin_port = htons(port);
    //Bind the port
    int bRet = ::bind(_msock, (struct sockaddr *)&_maddr, sizeof(_maddr));
    if(bRet == -1) {
        return false;
    }
    return true;
}

bool Socket::Listen() const {
    if(!IsValid()) {
        return false;
    }
    int lRet = ::listen(_msock, _MAXCONNECTIONS);
    if(lRet == -1) {
        return false;
    }
    return true;
}

bool Socket::Accept(Socket &s) const {
    int aLen = sizeof(_maddr);
    s._msock = ::accept(_msock, (sockaddr *)&_maddr, (socklen_t *)&aLen);
    if(s._msock <= 0) {
        return false;
    }
    return true;
}

bool Socket::Connect(const std::string host, const unsigned int port) {
    if(!IsValid()) {
        return false;
    }
    //UNIX pre-connect vars
    struct hostent *he;
    if((he = gethostbyname(host.c_str())) == NULL) {
    	cout << "Socket::Connect(): Failed to convert " << host.c_str() << " to an IP" << endl;
    }
    _maddr.sin_family = AF_INET;
    _maddr.sin_port = htons(port);
    memcpy(&_maddr.sin_addr, he->h_addr_list[0], he->h_length);
    //Are we allowed to create a connection?
    //cout << "Socket::Connect(): Attempting to establish connection to " << host.c_str() << ":" << port << " (" << he->h_addr_list[0] << ")" << endl;
    //Yes, Connect...
    int status = ::connect(_msock, (sockaddr *)&_maddr, sizeof(_maddr));
    if(status == 0) {
       //cout << "Socket::Connect(): Connection Successful..." << endl;
       return true;
    }
    std::cout << "Socket::Connect(): Failed to connect: " << status << ", errno " << errno << endl;
    return false;    
}

bool Socket::Close() {
    if(!IsValid()) {
        return false;       
    }
    int cRet = ::close(_msock);
    return cRet == 0;
}

bool Socket::Send(const std::string message) const {
    int sRet = ::send(_msock, message.c_str(), message.size(), MSG_NOSIGNAL);
    if(sRet == -1) { 
        return false;
    }
    return true;
}

int Socket::Recieve(std::string &message) const {
    message = "";
    memset(socketBuffer, 0, _MAXRECV+1);
    int total = sizeof(socketBuffer) - 1;
    int received = 0;
    //Try the recieve
    int rRet = ::recv(_msock, socketBuffer, _MAXRECV, 0);
    //cout << "DEBUG: (recv): msock: " << _msock << ", buffer: " << socketBuffer << ", returnCode: " << rRet << endl; 
    //Return commands
    switch(rRet) {
        case -1:
           std::cout << "Socket::Recieve() Status: -1, errno: " << errno << "\n";
           return -1;

        case 0:
        	std::cout << "Socket::Recieve(): Server issued disconnect command.\n";
            return 0;

        default:
            message = socketBuffer;
            return rRet;
    }
}

void Socket::SetNonBlocking(const bool status) {
	int options;
    options = fcntl(_msock, F_GETFL);
    if(options < 0) {
        return;
    }
    if(status) {
        options = (options | O_NONBLOCK);
    }
    else {
        options = (options & ~O_NONBLOCK);
    }
    fcntl(_msock, F_SETFL, options);
}
