# Phantom Bot Twitch IRC Project
# CURRENT VERSION: Alpha 3
## By Robert C. Fritzen (Phantom139)
## Written & Compiled on Ubuntu 16.04 LTS

### Prerequisites ###
No Libraries Required!!! This project uses all native Linux code. You'll just need the 'cmake' package to build it!

### Setup Instructions ###
Drop the files into a directory and open a terminal. cd to the directory and run the command 'cmake . && make' to compile, then run the code with ./PhantomBot

### Configuration Files ###
There are two bot config files you can use.

1. botconfig.txt contains information you'll need to obtain to run the bot You'll need to insert your account name associated with the bot, and the channel name of the channel you'd like the bot to be active in. Finally, you'll need to obtain your oauth code from Twitch. To obtain this, log into your bot account and naviagte to this link: http://twitchapps.com/tmi/ Copy the contents of the page and then paste it into the oauth line.
2. adminusers.txt is a line delimited file of usernames who will have "admin status" on bot commands. These users will have elevated permissions which allow access to built in administrative functions such as !debugmode, !reset, !disconnect, and other commands you may choose to add to the bot. (You can just as easily add multiple levels of admin to the bot by customizing the Admin.h/.cpp files to do so.

### Features ###
This is a very basic Twitch IRC bot with a very flexible and easy to navigate code-base. At it's core, this bot has the following features:

* Connection Interface via Linux Socket Instance
* Message Parsing System to Inquire and Parse Twitch IRC Commands
* Command Limit Instance to prevent the bot from exceeding the limits imposed by the Twitch API
* Logging system for both command and chat logging
* Admin User Interface to have quick access to defining users with administrative capabilities for in-stream commands
* Custom Command System to allow quick and easy deployment of custom chat commands

### Custom Chat Commands ###
As mentioned in the prior section, this bot has a very easy to use custom chat command interface. To create a custom chat command, follow the below instructions.

First and foremost, create a new C++ Header file, it would help you to follow the ccmd_x.h naming convention as not to differentiate from the other files in that directory. The bot uses a abstract class instance named CustomCommand, from which you will need to inherit. The class has a pure virtual function void Fire(std::string input) which must be overriden. At the most basic, here is a sample instance to use:
```c++
/**
    ccmd_mycommand.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 16.04 LTS
**/

#ifndef _CCMD_MYCOMMAND_H
#define _CCMD_MYCOMMAND_H

#include "CustomCommands.h"

class Command_MyCommand : public CustomCommand {
	public:
		/* Public Class Methods */
		//Constructor
		Command_MyCommand() : CustomCommand() { }
		//Destructor
		virtual ~Command_MyCommand() { }
		//Run the command
		virtual void Fire(std::string input) {
			std::string response = Lib::formatChatMessage("Hello World!!!");
			TwitchCommandLimit::fetchInstance().AddCommand(response);			
		}
};

#endif //_CCMD_MYCOMMAND_H
```

Once you have created a custom command, you'll need to add it to the command parser, which is located in the chatCommandDefinitions.h file in the base directory. Inside this file, you'll see a group of header include statements which point to the commands included with this bot, you'll need to add your header file, like so:
```c++
//Headers to all of your custom commands (Insert the path(s) to your custom command files here)
#include "CustomCommands/ccmd_time.h"
#include "CustomCommands/ccmd_isadmin.h"
#include "CustomCommands/ccmd_mycommand.h" //<--- ADD YOUR COMMAND HERE
```

Finally in the class instance below, you'll need to tell the bot to trigger your custom command upon a message. We'll use !hello for our example here, to do so, scroll down and add your command to the bot like so:
```c++
		//Initalize the instance
		void init() {
			if(initialized == true) {
				return;
			}
			initialized = true;
			CustomCommandManager::fetchInstance().AddCommand("!time", new Command_Time());
			CustomCommandManager::fetchInstance().AddCommand("!isadmin", new Command_IsAdmin());
			CustomCommandManager::fetchInstance().AddCommand("!hello", new Command_MyCommand());		
		}
```

And that's about it! From this, you should be able to make pretty much anything your coding capabilities allow you to do. Best of luck!

### Bug Reporting ###
This is still a very early project in the alpha stage, and therefore bugs are to be expected. If you encounter any, please report them on the issues page here.
