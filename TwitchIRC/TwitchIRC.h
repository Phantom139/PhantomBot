/**
    TwitchIRC.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _TWITCHIRC_H
#define _TWITCHIRC_H

#include "../include.h"
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
         TwitchIRC(const std::string nick, const std::string usr, const std::string pass, const std::string addr, unsigned int port, const std::string channel);    
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
         bool SendChatMessage(const std::string message);

     private:
         /* Private Class Methods */
         //Function called during the update to check for new messages
         bool fetchServerMessage(std::string &message);

         /* Private Class Members */
         //Thread instance which runs the AutoPing command
         std::thread *autoping_thread;
         //The address of the IRC Server
         std::string serverAddr;
         //The port
         unsigned int serverPort;
         //Name of channel connected to
         std::string _connectedChannel;
         //Socket object
         Socket *_socketObj;
};

#endif //_TWITCHIRC_H
