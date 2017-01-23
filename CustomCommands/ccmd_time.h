/**
    time.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _CCMD_TIME_H
#define _CCMD_TIME_H

#include "CustomCommands.h"

class Command_Time : public CustomCommand {
	public:
		/* Public Class Methods */
		//Constructor
		Command_Time() : CustomCommand() { }
		//Destructor
		virtual ~Command_Time() { }
		//Run the command
		virtual void Fire(string input) {
			string response = Lib::formatChatMessage("It is currently " + Lib::currentTime() + ".");
			TwitchCommandLimit::fetchInstance().AddCommand(response);			
		}
};

#endif //_CCMD_TIME_H
