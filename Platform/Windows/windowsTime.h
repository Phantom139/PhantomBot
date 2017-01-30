/**
	windowsTime.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#if defined(PHANTOMBOT_WINDOWS)

	#ifndef WINDOWS_TIME_H
	#define WINDOWS_TIME_H

		class Time : public GTime {
			public:
				static void sysTime(TimeVars &c);
				static void utcTime(TimeVars &c);
				static time_t makeGMTime(TimeVars &c);
		};

	#endif //WINDOWS_TIME_H

#endif //PHANTOMBOT_WINDOWS