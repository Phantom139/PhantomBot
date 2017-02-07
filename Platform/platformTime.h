/**
	platformTime.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H

#if USE_SYS_TIME == 1
	#include <sys/time.h>
#endif

struct TimeVars {

	S32 years;
	S32 months;
	S32 dayOfWeek;
	S32 dayNum;
	S32 hours;
	S32 minutes;
	S32 seconds;
	S32 miliseconds;

	TimeVars() : years(0), months(0), dayOfWeek(0), dayNum(0), hours(0), minutes(0), seconds(0), miliseconds(0) { }

	TimeVars(S32 yrs, S32 mo, S32 dow, S32 day, S32 hr, S32 min, S32 sec, S32 ms) : 
		years(yrs), months(mo), dayOfWeek(dow), dayNum(day), hours(hr), minutes(min), seconds(sec), miliseconds(ms) { }

	//Compare two time values and return a result similar to strcmp() where smaller == -1, equal == 0, and larger == 1
	S32 compare(const TimeVars &c) {
		S32 cYears = (years > c.years) ? 1000000 : (years == c.years ? 0 : -1000000);
		S32 cMonths = (months > c.months) ? 100000 : (months == c.months ? 0 : -100000);
		S32 cDayNumber = (dayNum > c.dayNum) ? 10000 : (dayNum == c.dayNum ? 0 : -10000);
		S32 cHours = (hours > c.hours) ? 1000 : (hours == c.hours ? 0 : -1000);
		S32 cMinutes = (minutes > c.minutes) ? 100 : (minutes == c.minutes ? 0 : -100);
		S32 cSeconds = (seconds > c.seconds) ? 10 : (seconds == c.seconds ? 0 : -10);
		S32 cMiliseconds = (miliseconds > c.miliseconds) ? 1 : (miliseconds == c.miliseconds ? 0 : -1);
		//Add everything up!
		S32 result = cYears + cMonths + cDayNumber + cHours + cMinutes + cSeconds + cMiliseconds;
		if (result > 0) {
			return 1;
		}
		else if (result < 0) {
			return -1;
		}
		return 0;
	}

	bool operator==(const TimeVars &t) {
		return !!(compare(t) == 0);
	}

	bool operator!=(const TimeVars &t) {
		return !!(compare(t) != 0);
	}

	bool operator>(const TimeVars &t) {
		return !!(compare(t) == 1);
	}

	bool operator>=(const TimeVars &t) {
		return compare(t) >= 0;
	}

	bool operator<(const TimeVars &t) {
		return compare(t) == -1 ? true : false;
	}

	bool operator<=(const TimeVars &t) {
		return compare(t) <= 0;
	}

};

class GTime {
	public:
		static UFC32 fetchTimestamp();
		static void fetchSysTime(ACHAR *dst);
		static void fetchDateString(ACHAR *dst);

		static time_t makeGMTime(TimeVars &c);

		/* If we have access to <sys/time.h>, define the time overlay */
		#if USE_SYS_TIME == 1
			static void sysTime(TimeVars &c);
			static void utcTime(TimeVars &c);
		#endif
};


#endif //PLATFORM_TIME_H