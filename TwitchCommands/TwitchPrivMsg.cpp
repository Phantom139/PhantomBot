/**
    TwitchPrivMsg.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#include "TwitchCommandProcess.h"

bool TwitchPrivMsg::Process(const std::string incoming) {
    std::string name, message, response;
    //Strip the username and their message
    std::string cName = _tcl->Channel();
    size_t nameEnd = incoming.find("!");
    size_t messageStart = incoming.find(cName + " :") + cName.size() + 2;
    //The correct format is :NAME!, test here
    if(incoming[0] == ':' && nameEnd != string::npos) {
        //Good!
        for(size_t i = 1; i < nameEnd; i++) {
        	name.push_back(incoming[i]);
        }
    }
    //Fetch the message content
    if(messageStart != string::npos) {
    	for(size_t i = messageStart; i < incoming.size(); i++) {
    		message.push_back(incoming[i]);
    	}
    }
    //Push to log / console
    cout << "Chat: " << name << ": " << message << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{Chat} " + name + ": " + message);	    
    
    //Process commands here!!!
    if(message.find("!time") != std::string::npos) {
    	response = formatChatMessage("It is currently " + Lib::currentTime() + ".");
    	_tcl->AddCommand(response);	
    }
    
    if(message.find("!isadmin") != std::string::npos) {
        bool isAdmin = _tcl->adminObj()->CheckAdminStatus(name);
    	response = formatChatMessage(name + (isAdmin ? " is" : " is not") + " flagged as an administrator.");
    	_tcl->AddCommand(response);	
    }
    
	return true;
}

std::string TwitchPrivMsg::formatChatMessage(const std::string message) {
	const std::string format = "PRIVMSG " + _tcl->Channel() + " :" + message + "\r\n";
	return format;
}
