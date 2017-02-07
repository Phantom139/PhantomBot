/**
	windowsTime.cpp
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "../../include.h"
#ifdef PHANTOMBOT_WINDOWS

	void Time::sysTime(TimeVars &c) {
		SYSTEMTIME sTime;
		GetLocalTime(&sTime);

		c.years = (S32)sTime.wYear;
		c.months = (S32)sTime.wMonth;
		c.dayOfWeek = (S32)sTime.wDayOfWeek;
		c.dayNum = (S32)sTime.wDay;
		c.hours = (S32)sTime.wHour;
		c.minutes = (S32)sTime.wMinute;
		c.seconds = (S32)sTime.wSecond;
		c.miliseconds = (S32)sTime.wMilliseconds;
	}

	void Time::utcTime(TimeVars &c) {
		SYSTEMTIME sTime;
		GetSystemTime(&sTime);

		c.years = (S32)sTime.wYear;
		c.months = (S32)sTime.wMonth;
		c.dayOfWeek = (S32)sTime.wDayOfWeek;
		c.dayNum = (S32)sTime.wDay;
		c.hours = (S32)sTime.wHour;
		c.minutes = (S32)sTime.wMinute;
		c.seconds = (S32)sTime.wSecond;
		c.miliseconds = (S32)sTime.wMilliseconds;
	}

	time_t Time::makeGMTime(TimeVars &c) {
		struct tm tm;
		memset(&tm, 0, sizeof(tm));

		tm.tm_year = c.years - 1900; 
		tm.tm_mon = c.months - 1;
		tm.tm_mday = c.dayNum;
		tm.tm_hour = c.hours;
		tm.tm_min = c.minutes;
		tm.tm_sec = c.seconds;
		tm.tm_isdst = -1; 

		return mktime(&tm);
	}

#endif