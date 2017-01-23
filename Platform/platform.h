/**
	platform.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

/*
	The cross-platform nature of this bot is very simplistic as 
	only two sections of the bot require cross-platform functioning,
	this being the network connection (Sockets) and some of the 
	simple threading capabilities.

	With the advent of C++11 to the project, the STL handles most
	of the threading requirements for Linux, leaving only the sockets

	This small library uses my work from my custom 2D game engine project,
	Galactic 2D (https://github.com/PhantomGamesDevelopment/Galactic-2D/blob/master/Source/EngineCore/PlatformCore/platform.h)
	to create a simple platform wrapper instance for the project.
*/

#include "platformTypes.h"

#ifndef PLATFORM_H
#define PLATFORM_H

	/* 
	This Platform Script handles the loading of the 
	background functioning which enables some basic 
	cross-platform functionality.
	*/

	//Step 1: Detect Platform
	/* Simple means to detect the platform */
	#if defined(_WIN64) || defined(_WIN32)
		#define PHANTOMBOT_WINDOWS 1
	#elif defined(__linux) || defined(__unix)
		#define PHANTOMBOT_LINUX 1
	#else
		#error "Undefined or unsupported platform instance, please see platform.h to add in capabilities for your platform."
	#endif

	//Step 2: Load Platform Specific Info
	#if defined(PHANTOMBOT_WINDOWS)
		#include "platformWindows.h"
		#include "loadWindows.h"
	#elif defined(PHANTOMBOT_LINUX)
		#include "platformLinux.h"
		#include "loadLinux.h"
	#else
		#error "How did you get here?"
	#endif

	//Step 3: Override Generic Platform Info
	typedef PlatformTypes::s_int_8 S8;
	typedef PlatformTypes::s_int_16 S16;
	typedef PlatformTypes::s_int_32 S32;
	typedef PlatformTypes::s_int_64 S64;
	typedef PlatformTypes::u_int_8 U8;
	typedef PlatformTypes::u_int_16 U16;
	typedef PlatformTypes::u_int_32 U32;
	typedef PlatformTypes::u_int_64 U64;
	typedef PlatformTypes::A_CHAR ACHAR;
	typedef PlatformTypes::W_CHAR WCHAR;
	typedef PlatformTypes::T_CHAR TCHAR;
	typedef PlatformTypes::char_8 UTF8;
	typedef PlatformTypes::char_16 UTF16;
	typedef PlatformTypes::char_32 UTF32;
	typedef PlatformTypes::SIZE_T SIZE_T;
	typedef PlatformTypes::SIZE_T_S SIZE_T_S;

#endif //PLATFORM_H