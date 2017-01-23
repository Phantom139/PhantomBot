/**
    TwitchCommandLimit.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandLimit.h"

/**
    TwitchCommandLimit Struct
**/

TwitchCommandLimit::TwitchCommandLimit() : aSock(NULL), currentSendCount(0), forcedSendCount(0), isModOrOp(false), channel(), debugMode(false) {
    gettimeofday(&curTVal, 0);
    gettimeofday(&curFVal, 0);
}

void TwitchCommandLimit::Init(Socket *sO, std::string cName) {
	if(!sO) {
		cout << "Cannot init the TCL without a socket" << endl;
		return;
	}
	aSock = sO;
	channel = cName;
}

void TwitchCommandLimit::ProcessUserState(const std::string command) {
	if(!aSock) {
		cout << "No socket object" << endl;
		return;
	}
    //We only need to know if we have op/mod status, look for it...
    if(command.find("mod=1") != string::npos) {
        if(!isModOrOp) {
        	std::cout << "BOT: Gained Op/Mod Status..." << endl;
        }
        isModOrOp = true;
    }
    else {
        if(isModOrOp) {
        	std::cout << "BOT: Lost Op/Mod Status..." << endl;
        }
        isModOrOp = false;
    }    
}

void TwitchCommandLimit::AddCommand(const std::string command) {
    commands.push(command);
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Added command '" + Lib::formatForPrint(command) + "'.");
    std::cout << "BOT: Command '" << Lib::formatForPrint(command).c_str() << "' added to queue..." << endl;
}

void TwitchCommandLimit::PushCommand(const std::string command) {
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Attempting to push command '" + Lib::formatForPrint(command) + "'.");
    std::cout << "BOT: Command '" << command.c_str() << "' added to queue under FORCE priority.. attempting to send now." << endl;
    //Check if it's been 30s since our last "push"
    timeval cur;
    gettimeofday(&cur, 0); 
    if((cur.tv_sec - curFVal.tv_sec) >= 30) {
        forcedSendCount = 0;
    }
    //If it hasn't been 30s, we need to verify that we have "allocation" available to force a mesage through
    if(forcedSendCount >= COMMAND_LIMIT_FORCED) {
        //we're out of FORCE spaces, check our normal space?
        if((isModOrOp && currentSendCount >= COMMAND_LIMIT_OPMOD-1)
           || (!isModOrOp && currentSendCount >= COMMAND_LIMIT_NORMAL-1)) {
            //We're currently over the command limit we're allocated..
            std::cout << "BOT: Unable to force command '" <<  Lib::formatForPrint(command).c_str() << "', currently at command limit, command has been added to the normal queue and will be pushed once it can." << endl;
            Lib::writeToLog("PhantomBotLog.txt", "{C++} 'Cannot push command '" + Lib::formatForPrint(command) + "', out of available message allocation limit.");
            AddCommand(command);
            return;
        }
        else {
            //We have some space in the normal queue, run it there
            if(currentSendCount == 0) {
                gettimeofday(&curTVal, 0);
    		}
    		currentSendCount++;
    		SendCommand(command);
        }                
    }
    //We've got some room, fire it!
    if(forcedSendCount == 0) {
        gettimeofday(&curFVal, 0);
    }
    forcedSendCount++;
    SendCommand(command);                       
}

void TwitchCommandLimit::Update() {
	if(!aSock) {
		cout << "No socket object" << endl;
		return;
	}
    timeval cur;
    gettimeofday(&cur, 0);
    std::string nextCmd;
    //Check the time
    if((cur.tv_sec - curTVal.tv_sec) >= 30) {
        //All good!
        currentSendCount = 0;
    }
    //Do we have anything to process?
    while(!commands.empty()) {
        //Check how many commands we've sent
        if((isModOrOp && currentSendCount >= COMMAND_LIMIT_OPMOD-1)
           || (!isModOrOp && currentSendCount >= COMMAND_LIMIT_NORMAL-1)) {
            //We're currently over the command limit we're allocated..
            // Stop here.
            break;
        }
        //We're ok to process commands, grab the nextCmd command and pop it from the list
        nextCmd = commands.front();
        commands.pop();
        //Add one to our counter, set the timer if zero
        if(currentSendCount == 0) {
            gettimeofday(&curTVal, 0);
        }
        currentSendCount++;
        //Send it!          
        SendCommand(nextCmd);
    }
}

const std::string TwitchCommandLimit::Channel() const {
	return channel;
}

void TwitchCommandLimit::SendCommand(const std::string command) {
	if(!aSock) {
		cout << "No socket object" << endl;
		return;
	}
	std::cout << "BOT: Attempting to send command '" << Lib::formatForPrint(command).c_str() << "' to server." << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Attempting to send command '" + Lib::formatForPrint(command) + "'.");
    if(!aSock->Send(command)) {
        Lib::writeToLog("PhantomBotLog.txt", "{C++} Command delivery failed.");
    	std::cout << "BOT: Command '" << Lib::formatForPrint(command).c_str() << "' failed to send." << endl;        	
    }
    else {
    	std::cout << "BOT: Command '" << Lib::formatForPrint(command).c_str() << "' successfully sent." << endl;
    }
}

const bool TwitchCommandLimit::DebugMode() const {
	return debugMode;
}

const bool TwitchCommandLimit::AdminOnlyMode() const {
	return adminOnlyMode;
}

TwitchCommandLimit &TwitchCommandLimit::fetchInstance() {
	if(managedSingleton<TwitchCommandLimit>::instance() == NULL) {
		managedSingleton<TwitchCommandLimit>::createInstance();
	}
	return *(managedSingleton<TwitchCommandLimit>::instance());
}
