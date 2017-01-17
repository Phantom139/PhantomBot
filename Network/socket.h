/**
    socket.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#ifndef _SOCKET_H
#define _SOCKET_H

#include "../include.h"

#define _MAXHOSTNAME 200
#define _MAXCONNECTIONS 5
#define _MAXRECV 1024

/*
Socket Class
A basic UNIX socket object
*/
class Socket {
    public:
        /* Public Class Methods */
        //Constructor
        Socket();
        //Destructor
        virtual ~Socket();   

        /* Server */
        //Create the socket
        bool Create();
        //Bind the socket to a port
        bool Bind(const unsigned int port);
        //Listen for incoming transmissions
        bool Listen() const;
        //Accept Requests
        bool Accept(Socket &s) const;

        /* Client */ 
        //Connect to a specified source
        bool Connect(const std::string host, const unsigned int port);

        /* Default Functioning */
        //Close the socket
        bool Close();
        //Send information through the socket
        bool Send(const std::string message) const;
        //Recieve information from the socket
        int Recieve(std::string &message) const;
        //Set the socket's non blocking status
        void SetNonBlocking(const bool status = true);
        //Is the active socket valid?
        bool IsValid() const { return _msock != -1; }

    private:
        /* Private Class Members */
        //The stored socket instance
        int _msock;  
        //The Socket's address
        sockaddr_in _maddr;
        //Socket string buffer
        char *socketBuffer;
};


#endif // _SOCKET_H
