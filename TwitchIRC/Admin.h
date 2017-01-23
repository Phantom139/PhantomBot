/**
    Admin.h
    PhantomBot Project
    By: Robert F. (Phantom139)
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
		bool CheckAdminStatus(string username);
		//Update the admin list
		void UpdateAdminList(); 
		//Fetch the admin singleton
		static Admin &fetchInstance();
	
	private:
		/* Private Class Members */
		//Admin list
		vector<string> adminList;
};

#endif //_TWITCHADMIN_H
