/**
    TwitchUserState.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandProcess.h"

bool TwitchUserState::Process(const string incoming) {
    cout << "BOT: Recieved USERSTATE Command: '" << Lib::formatForPrint(incoming).c_str() << "'." << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Recieved USERSTATE Command: '" + Lib::formatForPrint(incoming) + "'.");
	TwitchCommandLimit::fetchInstance().ProcessUserState(incoming);
	return true;
}

TwitchUserState &TwitchUserState::fetchInstance() {
	if(managedSingleton<TwitchUserState>::instance() == NULL) {
		managedSingleton<TwitchUserState>::createInstance();
	}
	return *(managedSingleton<TwitchUserState>::instance());
}
