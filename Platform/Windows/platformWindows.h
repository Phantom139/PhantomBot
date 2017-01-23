/**
	platformWindows.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#if defined(PHANTOMBOT_WINDOWS)

	#ifndef PLATFORM_WINDOWS_H
	#define PLATFORM_WINDOWS_H

		struct PlatformTypes : public GPlatformTypes {
			#ifdef _WIN64
				typedef unsigned __int64 SIZE_T;
				typedef __int64 SIZE_T_S;
				#define USING_64_BIT
			#else
				typedef unsigned long SIZE_T;
				typedef long SIZE_T_S;
				#undef USING_64_BIT
			#endif
		};

		#define USE_SYS_TIME 0

	#endif //PLATFORM_WINDOWS_H

#endif //PHANTOMBOT_WINDOWS