/**
	windowsSocket.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#if defined(PHANTOMBOT_WINDOWS)

	#ifndef PLATFORM_WINDOWS_SOCKET_H
	#define PLATFORM_WINDOWS_SOCKET_H

		class Socket : public GeneralSocket {
			public:
				Socket();
				virtual ~Socket();

				virtual bool create();
				virtual bool bind(const U32 port);
				virtual bool listen() const;
				virtual bool accept(Socket &s);
				virtual SocketReturnCode connect(UFC32 host, const U32 port);
				virtual bool close();
				virtual bool send(UFC32 message) const;
				virtual SocketReturnCode receive(U8 *buffer, S32 bufferSize, S32 *bytesRead) const;
				virtual void setNonBlocking(const bool status = true);
				virtual bool isValidSocket() const;

			private:
				SOCKET sObj;
				sockaddr_in _mAddr;
		};

	#endif //PLATFORM_WINDOWS_SOCKET_H

#endif //PHANTOMBOT_WINDOWS