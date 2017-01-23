/**
    TwitchCommandProcess.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _TWITCHCOMMANDPROCESS_H
#define _TWITCHCOMMANDPROCESS_H

#include "../include.h"
#include "../Lib/lib.h"
#include "../TwitchIRC/TwitchCommandLimit.h"
#include "../CustomCommands/CustomCommands.h"

/*
TwitchCommand Class
Virtual class instance for processing commands sent from the TwitchIRC server
*/
class TwitchCommand {
    public:    
        /* Public Class Methods */
        //Constructor
        TwitchCommand(string n) : name(n) { }
        //Destructor
        virtual ~TwitchCommand() { }
        
        //Process the command
        virtual bool Process(const string incoming) = 0;
        //Return the name of this command instance
        virtual const string Name() { return name; };
        
	protected:
		string name;
};

/*
TwitchPing Class
Handles the PING message sent by Twitch
*/
class TwitchPing : public TwitchCommand {
	public:
		/* Public Class Methods */
		//Constructor
		TwitchPing() : TwitchCommand("Ping") { }
		//Destructor
		virtual ~TwitchPing() { }
		//Process the command
		virtual bool Process(const string incoming);
        //Fetch singleton instance
    	static TwitchPing &fetchInstance();
};

/*
TwitchPrivMsg Class
Handles the PRIVMSG message sent by Twitch
*/
class TwitchPrivMsg : public TwitchCommand {
	public:
		/* Public Class Methods */
		//Constructor
		TwitchPrivMsg() : TwitchCommand("PrivMsg") { }
		//Process the command
		virtual bool Process(const string incoming);
        //Fetch singleton instance
    	static TwitchPrivMsg &fetchInstance();          
        
	private:
		/* Private Class Methods */
		//Format a chat message
		string formatChatMessage(const string message);
};    

/*
TwitchUserState Class
Handles the USERSTATE message sent by Twitch
*/
class TwitchUserState : public TwitchCommand {
	public:
		/* Public Class Methods */
		//Constructor
		TwitchUserState() : TwitchCommand("UserState") { }
		//Process the command
		virtual bool Process(const string incoming);
        //Fetch singleton instance
    	static TwitchUserState &fetchInstance();            
};  

#endif //_TWITCHCOMMANDPROCESS_H
