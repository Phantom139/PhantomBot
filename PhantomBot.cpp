/**
    PhantomBot.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "Lib/lib.h"
#include "TwitchIRC/TwitchIRC.h"

int main(void) {
	srand((U32)time(NULL));
	//read the config
	ACHAR line[512];
	vector<string> config;
	fstream f("botconfig.txt", ios::in);
	while(!f.eof()) {
		f.getline(line, 512);
		config.push_back(line);
		memset(&line[0], 0, sizeof(line));
	}
	//Set stuff up...
	if(config.size() >= 5) {
		TwitchIRC irc(config[0], config[0], config[4], config[1], (U32)atoi(config[2].c_str()), config[3]);
		while(irc.SocketActive()) {
			irc.Update();
		}
	}
	else {
		cout << "There was an error in your 'botconfig.txt' file, contact Phantom139 for support" << endl;
	}
	cout << "Closing program..." << endl;
	return 0;
}
