/**
    TwitchPrivMsg.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandProcess.h"

bool TwitchPrivMsg::Process(const string incoming) {
    string name, message;
    //Strip the username and their message
	Lib::stripMessage(incoming, name, message);
    //Push to log / console
    cout << "Chat: " << name << ": " << message << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{Chat} " + name + ": " + message);	    
    
    //Process commands here, but check if we're only doing it for admin users
    if(TwitchCommandLimit::fetchInstance().AdminOnlyMode()) {
    	if(!Admin::fetchInstance().CheckAdminStatus(name)) {
    		//Out of luck, kill here...
    		return true;
    	}
    }
    CustomCommandManager::fetchInstance().Process(incoming);

	return true;
}

TwitchPrivMsg &TwitchPrivMsg::fetchInstance() {
	if(managedSingleton<TwitchPrivMsg>::instance() == NULL) {
		managedSingleton<TwitchPrivMsg>::createInstance();
	}
	return *(managedSingleton<TwitchPrivMsg>::instance());
}
