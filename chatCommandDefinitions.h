/**
    chatCommandDefinitions.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _CCMDDEC_H
#define _CCMDDEC_H

//Generic Headers (Don't Touch)
#include "include.h"
#include "CustomCommands/CustomCommands.h"
//Headers to all of your custom commands (Insert the path(s) to your custom command files here)
#include "CustomCommands/ccmd_time.h"
#include "CustomCommands/ccmd_isadmin.h"
#include "CustomCommands/ccmd_adminonly.h"

/*
ChatCommandDecs Class
Handle class which contains and initalizes all of the custom chat command definitions
*/
class ChatCommandDecs {
	public:
		/* Public Class Methods */
		//Constructor
		ChatCommandDecs() : initialized(false) { }
		//Destructor
		~ChatCommandDecs() { }
		//Fetch the instance
		static ChatCommandDecs &fetchInstance() {
			if(managedSingleton<ChatCommandDecs>::instance() == NULL) {
				managedSingleton<ChatCommandDecs>::createInstance();
			}
			return *(managedSingleton<ChatCommandDecs>::instance());		
		}
		//Initalize the instance
		void init() {
			if(initialized == true) {
				return;
			}
			initialized = true;
			CustomCommandManager::fetchInstance().AddCommand("!time", new Command_Time());
			CustomCommandManager::fetchInstance().AddCommand("!isadmin", new Command_IsAdmin());
			CustomCommandManager::fetchInstance().AddCommand("!adminonly", new Command_AdminOnly());		
		}

	private:
		bool initialized;
};

#endif //_CCMDDEC_H
