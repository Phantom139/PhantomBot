/**
platformTypes.h
PhantomBot Project
By: Robert F. (Phantom139)
**/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*
	Windows and Linux handle size_t differently, so we need to make
	sure we handle that ourselves here. This simple template definition
	will ensure that the types are the same on both platforms
*/
template <typename bittype_32, typename bittype_64, int sizeofintptr> struct sizettype {
	//The empty definition, force a compile error.
};
template <typename bittype_32, typename bittype_64> struct sizettype<bittype_32, bittype_64, 4> {
	typedef bittype_32 sizet_ptr;
};
template <typename bittype_32, typename bittype_64> struct sizettype<bittype_32, bittype_64, 8> {
	typedef bittype_64 sizet_ptr;
};

/*
	Note: This implementation follows the same route as does my
	Galactic-2D engine project. Define a list of "generic" types,
	and then a list of platform-dependent types before overriding 
	all types with the standard list that the remainder of the 
	project will use.
*/
struct GPlatformTypes {
	//Signed Types
	typedef signed char s_int_8;
	typedef signed short int s_int_16;
	typedef signed int s_int_32;
	typedef signed long long s_int_64;

	//Unsigned Types
	typedef unsigned char u_int_8;
	typedef unsigned short int u_int_16;
	typedef unsigned int u_int_32;
	typedef unsigned long long u_int_64;

	//Characters
	typedef char A_CHAR;
	typedef wchar_t W_CHAR;
	typedef W_CHAR T_CHAR;
	typedef u_int_8 char_8;
	typedef u_int_16 char_16;
	typedef u_int_32 char_32;

	//size_t
	typedef sizettype<u_int_32, u_int_64, sizeof(void *)>::sizet_ptr U_SIZET_PTR;
	typedef sizettype<s_int_32, s_int_64, sizeof(void *)>::sizet_ptr S_SIZET_PTR;
	typedef U_SIZET_PTR SIZE_T;
	typedef S_SIZET_PTR SIZE_T_S;

	//others
	typedef signed long s_long;
	typedef unsigned long u_long;
};

#endif //PLATFORM_TYPES_H