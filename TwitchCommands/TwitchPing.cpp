/**
    TwitchPing.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandProcess.h"

bool TwitchPing::Process(const string incoming) {
    cout << "BOT: Recieved PING request, responding..." << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Recieved PING request, responding...");
	//const string response = "PONG " + TwitchCommandLimit::fetchInstance().Channel();
	const string response = "PONG :tmi.twitch.tv\r\n";
	TwitchCommandLimit::fetchInstance().PushCommand(response);
	return true;
}

TwitchPing &TwitchPing::fetchInstance() {
	if(managedSingleton<TwitchPing>::instance() == NULL) {
		managedSingleton<TwitchPing>::createInstance();
	}
	return *(managedSingleton<TwitchPing>::instance());
}
