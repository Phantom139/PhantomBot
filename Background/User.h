/**
	User.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#ifndef USER_H
#define USER_H

#include "../include.h"

class User {
	public:
		User(string n);
		~User();

	private:
		string name;
};

#endif //USER_H