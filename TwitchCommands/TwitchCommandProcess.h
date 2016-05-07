/**
    TwitchCommandProcess.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#ifndef _TWITCHCOMMANDPROCESS_H
#define _TWITCHCOMMANDPROCESS_H

#include "../include.h"
#include "../Lib/lib.h"
#include "../TwitchIRC/TwitchCommandLimit.h"

/*
TwitchCommand Class
Virtual class instance for processing commands sent from the TwitchIRC server
*/
class TwitchCommand {
    public:    
        /* Public Class Methods */
        //Constructor
        TwitchCommand(TwitchCommandLimit *cmdLmt) : _tcl(cmdLmt) { }
        //Destructor
        virtual ~TwitchCommand() { }
        
        //Process the command
        virtual bool Process(const std::string incoming) = 0;
        //Return the name of this command instance
        virtual const std::string Name() const = 0;
        
    protected:
    	/* Protected Class Members */
    	//The command processing interface
    	TwitchCommandLimit *_tcl;
};

/*
TwitchPing Class
Handles the PING message sent by Twitch
*/
class TwitchPing : public TwitchCommand {
	public:
		/* Public Class Methods */
		//Constructor
		TwitchPing(TwitchCommandLimit *cmdLmt) : TwitchCommand(cmdLmt) { }
		//Process the command
		virtual bool Process(const std::string incoming);
		//Return the name of this command instance
        virtual const std::string Name() const { 
        	return "Ping";
        }
};

/*
TwitchPrivMsg Class
Handles the PRIVMSG message sent by Twitch
*/
class TwitchPrivMsg : public TwitchCommand {
	public:
		/* Public Class Methods */
		//Constructor
		TwitchPrivMsg(TwitchCommandLimit *cmdLmt) : TwitchCommand(cmdLmt) { }
		//Process the command
		virtual bool Process(const std::string incoming);
		//Return the name of this command instance
        virtual const std::string Name() const { 
        	return "PrivMsg";
        }
        
	private:
		/* Private Class Methods */
		//Format a chat message
		std::string formatChatMessage(const std::string message);
};    

/*
TwitchUserState Class
Handles the USERSTATE message sent by Twitch
*/
class TwitchUserState : public TwitchCommand {
	public:
		/* Public Class Methods */
		//Constructor
		TwitchUserState(TwitchCommandLimit *cmdLmt) : TwitchCommand(cmdLmt) { }
		//Process the command
		virtual bool Process(const std::string incoming);
		//Return the name of this command instance
        virtual const std::string Name() const { 
        	return "UserState";
        }
};  

#endif //_TWITCHCOMMANDPROCESS_H
