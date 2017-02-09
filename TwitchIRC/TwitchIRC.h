/**
    TwitchIRC.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _TWITCHIRC_H
#define _TWITCHIRC_H

#include "../Lib/lib.h"
#include "TwitchCommandLimit.h"
#include "Admin.h"
#include "../TwitchCommands/TwitchCommandProcess.h"
#include "../CustomCommands/CustomCommands.h"
#include "../chatCommandDefinitions.h"

//Interval in which to ping the server to keep the connection alive, by default it's 4 minutes (240000MS)
#define PING_INTERVAL 240000

/*
TwitchIRC Class
Wrapper instance for connection and persistence
*/
class TwitchIRC {

     public:
         /* Default Stuff */
         //Constructor
         TwitchIRC(UFC32 nick, UFC32 usr, UFC32 pass, UFC32 addr, U32 port, UFC32 channel);
         //Destructor
         ~TwitchIRC();

         /* Class Commands */
         //Update function, called once per frame to handle updates
         void Update();
         //Close the Socket connection
         void CloseSocket();
         //Check the status of the Socket
         bool SocketActive();
         //Send ping to server, ran once every 5 minutes to prevent premature disconnect
         void AutoPing();

         /* IRC Commands, Handled by the TwitchCommandLimit class */
         //Send a chat message
         bool SendChatMessage(UFC32 message);
		 //Process a console command
		 bool ProcessConsoleCommand(UFC32 input);

     private:
         /* Private Class Methods */
         //Function called during the update to check for new messages
         bool fetchServerMessage();

         /* Private Class Members */
         //Thread instance which runs the AutoPing command
         thread *autoping_thread;
         //The address of the IRC Server
         string serverAddr;
         //The port
         U32 serverPort;
         //Name of channel connected to
         string _connectedChannel;
         //Socket object
         Socket *_socketObj;
		 //Data buffer
		 U8 *buffer;
		 
		 string response;
};

#endif //_TWITCHIRC_H
