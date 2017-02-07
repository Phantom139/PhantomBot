/**
	PhantomBot.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "include.h"
#include "TwitchIRC/TwitchIRC.h"

#ifndef PHANTOM_BOT_H
#define PHANTOM_BOT_H

class PhantomBot {
	public:
		PhantomBot();
		~PhantomBot();

		static PhantomBot &fetchInstance();
		void init(vector<string> &config);

	private:
		void ircTick();
		void inputTick();

		bool initialized;
		bool wantsQuit;

		thread *inputThread;
		thread *ircThread;
		TwitchIRC *irc;
		string input;
};

#endif //PHANTOM_BOT_H