/**
    adminonly.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _CCMD_ADMINONLY_H
#define _CCMD_ADMINONLY_H

#include "CustomCommands.h"

class Command_AdminOnly : public CustomCommand {
	public:
		/* Public Class Methods */
		//Constructor
		Command_AdminOnly() : CustomCommand() { }
		//Destructor
		virtual ~Command_AdminOnly() { }
		//Run the command
		virtual void Fire(string input) {
			string name, message;
			Lib::stripMessage(input, name, message);		
			if(!Admin::fetchInstance().CheckAdminStatus(name)) {
				return;
			}
			//Get the input after the command
			SIZE_T postCmd = message.find("!adminonly") + 10;
			S32 v = atoi(message.substr(postCmd, message.length()).c_str());
			TwitchCommandLimit::fetchInstance().setAdminMode(v <= 0 ? false : true);
			//Post-process
			string pFlg = TwitchCommandLimit::fetchInstance().AdminOnlyMode() ? "Enabled" : "Disabled";
			string response = Lib::formatChatMessage("Admin-Only Command Mode " + pFlg + " by " + name + ".");
			TwitchCommandLimit::fetchInstance().AddCommand(response);			
		}
};

#endif //_CCMD_ADMINONLY_H
