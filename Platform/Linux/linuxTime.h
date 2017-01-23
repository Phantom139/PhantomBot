/**
	linuxTime.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#if defined(PHANTOMBOT_LINUX)

	#ifndef LINUX_TIME_H
	#define LINUX_TIME_H

		//Linux makes use of systime, and therefore we can
		// fork off to the standard time class.
		class Time : public GTime { };

	#endif //LINUX_TIME_H

#endif //PHANTOMBOT_LINUX