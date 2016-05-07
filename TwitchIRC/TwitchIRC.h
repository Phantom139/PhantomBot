/**
    TwitchIRC.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#ifndef _TWITCHIRC_H
#define _TWITCHIRC_H

#include "../include.h"
#include "../Lib/lib.h"
#include "TwitchCommandLimit.h"
#include "Admin.h"
#include "../TwitchCommands/TwitchCommandProcess.h"

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

         /* IRC Commands, Handled by the TwitchCommandLimit class */
         //Send a chat message
         bool SendChatMessage(const std::string message);

     private:
         /* Private Class Methods */
         //Function called during the update to check for new messages
         bool fetchServerMessage(std::string &message);

         /* Private Class Members */
         //CommandLimit instance attached to class
         TwitchCommandLimit *_tcl;
         //Name of channel connected to
         std::string _connectedChannel;
         //Socket object
         Socket *_socketObj;
         //Admin user tracker
         Admin *tAdmin;
         
         /* Twitch Command Interfaces */
         TwitchPing *_tPing;
         TwitchPrivMsg *_tPrivMsg;
         TwitchUserState *_tUserState;

};

#endif //_TWITCHIRC_H
