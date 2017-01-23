/**
    PhantomBot.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "Lib/lib.h"
#include "TwitchIRC/TwitchIRC.h"

int main(void) {
	srand((unsigned int)time(NULL));
	//read the config
	char line[512];
	std::vector<std::string> config;
	std::fstream f("botconfig.txt", std::ios::in);
	while(!f.eof()) {
		f.getline(line, 512);
		config.push_back(line);
		memset(&line[0], 0, sizeof(line));
	}
	//Set stuff up...
	if(config.size() >= 5) {
		TwitchIRC irc(config[0], config[0], config[4], config[1], (unsigned int)atoi(config[2].c_str()), config[3]);
		while(irc.SocketActive()) {
			irc.Update();
		}
	}
	else {
		std::cout << "There was an error in your 'botconfig.txt' file, contact Phantom139 for support" << endl;
	}
	std::cout << "Closing program..." << endl;
	return 0;
}
