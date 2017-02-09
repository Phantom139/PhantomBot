/**
    TwitchCommandLimit.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandLimit.h"

/**
    TwitchCommandLimit Struct
**/

TwitchCommandLimit::TwitchCommandLimit() : aSock(NULL), currentSendCount(0), isModOrOp(false), channel(), debugMode(false) {
	Time::utcTime(curTVal);
	Time::utcTime(curFVal);
}

void TwitchCommandLimit::Init(Socket *sO, string cName) {
	if(!sO) {
		cout << "Cannot init the TCL without a socket" << endl;
		return;
	}
	aSock = sO;
	channel = cName;
	updateThread = new thread(&TwitchCommandLimit::Update, this);
}

void TwitchCommandLimit::ProcessUserState(const string command) {
	if(!aSock) {
		cout << "No socket object" << endl;
		return;
	}
    //We only need to know if we have op/mod status, look for it...
    if(command.find("mod=1") != string::npos) {
        if(!isModOrOp) {
        	cout << "BOT: Gained Op/Mod Status..." << endl;
        }
        isModOrOp = true;
    }
    else {
        if(isModOrOp) {
        	cout << "BOT: Lost Op/Mod Status..." << endl;
        }
        isModOrOp = false;
    }    
}

void TwitchCommandLimit::AddCommand(const string command) {
    normalCommands.push(command);
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Added command '" + Lib::formatForPrint(command) + "'.");
    cout << "BOT: Command '" << Lib::formatForPrint(command).c_str() << "' added to queue..." << endl;
}

void TwitchCommandLimit::PushCommand(const string command) {
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Attempting to push command '" + Lib::formatForPrint(command) + "'.");
    cout << "BOT: Command '" << command.c_str() << "' added to queue under FORCE priority." << endl;
	forcedCommands.push(command);
}

void TwitchCommandLimit::Update() {
	while (aSock->isValidSocket()) {
		TimeVars cur;
		Time::utcTime(cur);
		string nextCmd;
		//Check the time
		if ((Time::makeGMTime(cur) - Time::makeGMTime(curFVal)) >= 30) {
			//All good!
			currentSendCount = 0;
		}
		//Do we have anything to process?
		while (!forcedCommands.empty()) {
			//Check how many commands we've sent
			if ((isModOrOp && currentSendCount >= COMMAND_LIMIT_OPMOD - 1)
				|| (!isModOrOp && currentSendCount >= COMMAND_LIMIT_NORMAL - 1)) {
				//We're currently over the command limit we're allocated..
				// Stop here.
				break;
			}
			//We're ok to process commands, grab the nextCmd command and pop it from the list
			nextCmd = forcedCommands.front();
			forcedCommands.pop();
			//Add one to our counter, set the timer if zero
			if (currentSendCount == 0) {
				Time::utcTime(curTVal);
			}
			//Send it!          
			SendCommand(nextCmd);
		}
		while (!normalCommands.empty()) {
			//Check how many commands we've sent
			if ((isModOrOp && currentSendCount >= COMMAND_LIMIT_OPMOD - 1)
				|| (!isModOrOp && currentSendCount >= COMMAND_LIMIT_NORMAL - 1)) {
				//We're currently over the command limit we're allocated..
				// Stop here.
				break;
			}
			//We're ok to process commands, grab the nextCmd command and pop it from the list
			nextCmd = normalCommands.front();
			normalCommands.pop();
			//Add one to our counter, set the timer if zero
			if (currentSendCount == 0) {
				Time::utcTime(curTVal);
			}
			//Send it!          
			SendCommand(nextCmd);
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	updateThread->join();
}

const string TwitchCommandLimit::Channel() const {
	return channel;
}

void TwitchCommandLimit::SendCommand(const string command) {
	if(!aSock) {
		cout << "No socket object" << endl;
		return;
	}
	cout << "BOT: Attempting to send command '" << Lib::formatForPrint(command).c_str() << "' to server." << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Attempting to send command '" + Lib::formatForPrint(command) + "'.");
    if(!aSock->send(command.c_str())) {
        Lib::writeToLog("PhantomBotLog.txt", "{C++} Command delivery failed.");
    	cout << "BOT: Command '" << Lib::formatForPrint(command).c_str() << "' failed to send." << endl;        	
    }
    else {
		currentSendCount++;
    	cout << "BOT: Command '" << Lib::formatForPrint(command).c_str() << "' successfully sent." << endl;
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
