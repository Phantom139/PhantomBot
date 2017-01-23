/**
	windowsTime.cpp
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "../../include.h"

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