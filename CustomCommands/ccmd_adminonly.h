/**
    adminonly.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
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
		virtual void Fire(std::string input) {
			std::string name, message;
			Lib::stripMessage(input, name, message);		
			if(!Admin::fetchInstance().CheckAdminStatus(name)) {
				return;
			}
			//Get the input after the command
			size_t postCmd = message.find("!adminonly") + 10;
			int v = atoi(message.substr(postCmd, message.length()).c_str());
			TwitchCommandLimit::fetchInstance().setAdminMode((bool)v);
			//Post-process
			std::string pFlg = TwitchCommandLimit::fetchInstance().AdminOnlyMode() ? "Enabled" : "Disabled";
			std::string response = Lib::formatChatMessage("Admin-Only Command Mode " + pFlg + " by " + name + ".");
			TwitchCommandLimit::fetchInstance().AddCommand(response);			
		}
};

#endif //_CCMD_ADMINONLY_H
