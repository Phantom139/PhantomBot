/**
	platformNetwork.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#ifndef PLATFORM_NETWORK_H
#define PLATFORM_NETWORK_H

#ifndef _MAXHOSTNAME
#define _MAXHOSTNAME 200
#endif

#ifndef _MAXCONNECTIONS
#define _MAXCONNECTIONS 5
#endif

#ifndef _MAXRECV
#define _MAXRECV 1024
#endif

class GeneralSocket {
	public:
		//Enumeration
		enum SocketReturnCode {
			Disconnected = 0,
			Connected,
			ConnectionFailed,
			NoError,
			RecieveError,
			Timeout,
			InvalidSocket,
			Unknown
		};

		GeneralSocket() { }
		virtual ~GeneralSocket() { }

		//General Methods
		virtual bool create() = 0;
		virtual bool bind(const U32 port) = 0;
		virtual bool listen() const = 0;
		virtual bool accept(GeneralSocket &s) { return false; }
		virtual SocketReturnCode connect(UFC32 host, const U32 port) = 0;
		virtual bool close() = 0;
		virtual bool shutdown() = 0;
		virtual bool send(UFC32 message) const = 0;
		virtual SocketReturnCode receive(ACHAR *buffer, S32 bufferSize, S32 *bytesRead) const = 0;
		virtual void setNonBlocking(const bool status = true) = 0;
		virtual bool isValidSocket() const = 0;

		//Callbacks
		virtual void onConnected() { }
		virtual void onConnectFailed() { }
		virtual void onSelfDisconnect() { }
		virtual void onServerDisconect() { }

	protected:
		ACHAR *inBuff;
};

//Easy Access Typedef
typedef GeneralSocket::SocketReturnCode SocketCode;

#endif //PLATFORM_NETWORK_H
