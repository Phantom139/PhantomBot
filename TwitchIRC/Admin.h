/**
    Admin.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#ifndef _TWITCHADMIN_H
#define _TWITCHADMIN_H

#include "../include.h"
#include "../Lib/lib.h"

/*
Admin Class
Handles actions for bot administration
*/
class Admin {
	public:
		/* Public Class Methods */
		//Constructor
		Admin();
		//Destructor
		~Admin();
		//Check admin status
		bool CheckAdminStatus(std::string username);
		//Update the admin list
		void UpdateAdminList();
	
	private:
		/* Private Class Members */
		//Admin list
		std::vector<std::string> adminList;
};

#endif //_TWITCHADMIN_H
