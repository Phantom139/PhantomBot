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
		void readInput(atomic<bool> &fromRun);
		void run();

		bool initialized;
		bool wantsQuit;

		thread *readInputThread;
		TwitchIRC *irc;
		string input;
};

#endif //PHANTOM_BOT_H