/**
    Admin.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "Admin.h"

Admin::Admin() {
	UpdateAdminList();
}

Admin::~Admin() {

}

bool Admin::CheckAdminStatus(string username) {
	for(SIZE_T i = 0; i < adminList.size(); i++) {
		if(username.compare(adminList[i]) == 0) {
			return true;
		}
	}
	return false;
}

void Admin::UpdateAdminList() {
    adminList.clear();
	fstream f("adminusers.txt", ios::in);
	ACHAR line[512];
	while(!f.eof()) {
		f.getline(line, 512);
		adminList.push_back(line);
		memset(&line[0], 0, sizeof(line));
	}
}

Admin &Admin::fetchInstance() {
	if(managedSingleton<Admin>::instance() == NULL) {
		managedSingleton<Admin>::createInstance();
	}
	return *(managedSingleton<Admin>::instance());
}
