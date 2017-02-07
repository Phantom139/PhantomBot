/**
    CustomCommandManager.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "CustomCommands.h"

CustomCommandManager::CustomCommandManager() {

}

CustomCommandManager::~CustomCommandManager() {

}

void CustomCommandManager::AddCommand(string trigger, CustomCommand *cmd) {
	CCMD custom(trigger, cmd);
	commandList.push_back(custom);
}

void CustomCommandManager::Process(string input) {
    //Split the message to find the trigger
    string username, message;
    Lib::stripMessage(input, username, message);
	for(SIZE_T i = 0; i < commandList.size(); i++) {
		if(commandList[i].trigger.compare(message.substr(0, commandList[i].trigger.length())) == 0) {
			commandList[i].instance->Fire(input);
		}
	}
}

CustomCommandManager &CustomCommandManager::fetchInstance() {
	if(managedSingleton<CustomCommandManager>::instance() == NULL) {
		managedSingleton<CustomCommandManager>::createInstance();
	}
	return *(managedSingleton<CustomCommandManager>::instance());
}
