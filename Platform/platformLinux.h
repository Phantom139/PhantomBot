/**
	platformLinux.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#if defined(PHANTOMBOT_LINUX)

	#ifndef PLATFORM_LINUX_H
	#define PLATFORM_LINUX_H

		struct PlatformTypes : public GPlatformTypes {
			#if defined(_LINUX64) || defined(_LP64)
				#define USING_64_BIT
			#else
				#undef USING_64_BIT
			#endif

			typedef unsigned int DWORD;
			typedef __SIZE_TYPE__ SIZE_T;
		};

	#endif //PLATFORM_LINUX_H

#endif //PHANTOMBOT_LINUX