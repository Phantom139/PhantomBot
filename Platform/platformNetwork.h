/**
	platformNetwork.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#ifndef PLATFORM_NETWORK_H
#define PLATFORM_NETWORK_H

#include "../include.h"

#define _MAXHOSTNAME 200
#define _MAXCONNECTIONS 5
#define _MAXRECV 1024

class GeneralSocket {
	protected:
		enum SocketReturnCode {
			Disconnected = 0,
			Connected,
			ConnectionFailed,
			NoError,
			RecieveError,
			InvalidSocket,
			Unknown
		};

	public:
		GeneralSocket();
		virtual ~GeneralSocket();

		//General Methods
		virtual bool create() = 0;
		virtual bool bind(const U32 port) = 0;
		virtual bool listen() const = 0;
		virtual bool accept(GeneralSocket &s) = 0;
		virtual SocketReturnCode connect(UFC32 host, const U32 port) = 0;
		virtual bool close() = 0;
		virtual bool shutdown() = 0;
		virtual bool send(UFC32 message) const = 0;
		virtual SocketReturnCode receive(U8 *buffer, S32 bufferSize, S32 *bytesRead) const = 0;
		virtual void setNonBlocking(const bool status = true) = 0;
		virtual bool isValidSocket() const = 0;

		//Callbacks
		virtual void onConnected();
		virtual void onConnectFailed();
		virtual void onSelfDisconnect();
		virtual void onServerDisconect();
};

#endif //PLATFORM_NETWORK_H