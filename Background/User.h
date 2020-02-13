/**
	User.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#ifndef USER_H
#define USER_H

#include "../include.h"

/*
	UserList: A class instance that contains a list of the users
*/
class UserList {
	public:
		UserList();
		~UserList();

		//saveData(): Save all of the user data to a file
		void saveData(string filePath);
		//loadData(): Load the user data from a file
		void loadData(string filePath);

		//addUser(User): Add a user to the database from an existing User object
		bool addUser(User u);
		//addUser(string): Add a new user to the database, set the string
		bool addUser(string n);
		//removeUser(User): Remove a user from the database by the User object
		bool removeUser(User u);
		//removeUser(string): Remove a user from the database by the name
		bool removeUser(string n);

		//Find a user instance by the name
		User &findUser(string n);

	private:
		vector<User> userList;
};

class User {
	public:
		User(string n);
		~User();

		void setActiveState(bool set = true) { active = set; }
		void addPoints(U64 add) { points += add; }
		void addPoints(S32 add) { points += add; }
		void reducePoints(U64 reduce) { points -= reduce; }
		void reducePoints(S32 reduce) { points -= reduce; }
		void resetPoints() { points = 0; }

		void setIsMod(bool val) { userIsMod = val; }
		void setIsSub(bool val) { userIsSub = val; }
		void setIsVIP(bool val) { userIsVIP = val; }
		void setIsHost(bool val) { userIsHost = val; }

	private:
		string name;
		bool active;
		bool userIsMod;
		bool userIsSub;
		bool userIsVIP;
		bool userIsHost;
		U64 points;
};

#endif //USER_H