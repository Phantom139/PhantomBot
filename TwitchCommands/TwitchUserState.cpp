/**
    TwitchUserState.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#include "TwitchCommandProcess.h"

bool TwitchUserState::Process(const std::string incoming) {
    cout << "BOT: Recieved USERSTATE Command: '" << Lib::formatForPrint(incoming).c_str() << "'." << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Recieved USERSTATE Command: '" + Lib::formatForPrint(incoming) + "'.");
	_tcl->ProcessUserState(incoming);
	return true;
}
