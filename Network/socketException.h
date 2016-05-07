/**
    socketException.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#ifndef _SOCKETEXCEPTION_H
#define _SOCKETEXCEPTION_H

#include "../include.h"
#include "../Lib/lib.h"

/*
SocketException Class
Handles errors and exceptions
*/
class SocketException {
    public:
        /* Public Class Methods */
        //Constructor
        SocketException(std::string e) : m(e) { };
        //Destructor
        ~SocketException() { };
        //Descriptor Output
        std::string Describe() { return m; }

    private:
        /* Private Class Members */
        //Description
        std::string m;

};

#endif //_SOCKETEXCEPTION_H
