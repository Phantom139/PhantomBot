/**
    lib.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#include "lib.h"

namespace Lib {

	Socket *createSocketAndConnect(const std::string addr, unsigned int port) {
		Socket *s = new Socket();
		if(!s->Create()) {
		    std::cout << "Lib::createSocketAndConnect(): Creation Failed" << std::endl;
		    return NULL;
		}
		if(!s->Connect(addr, port)) {
		    std::cout << "Lib::createSocketAndConnect(): Connection Failed" << std::endl;
		    return NULL;        
		}
		return s;
	}

	std::string currentTime() {
		time_t t = time(NULL);
		char *s = ctime(&t);
		s[strlen(s)-1] = 0;
		return std::string(s);
	}

	void writeToLog(std::string logLocation, std::string message) {
	    std::fstream f(logLocation.c_str(), std::fstream::app | std::fstream::out);
		std::string output;
		output = "[" + currentTime() + "]: " + message + "\n";
		f.write(output.c_str(), output.size());
		f.close();
	}
	
	std::string formatForPrint(std::string incoming) {
		std::string out = incoming;
		out.erase(std::remove(out.begin(), out.end(), '\r'), out.end());
		out.erase(std::remove(out.begin(), out.end(), '\n'), out.end());
		return out;
	}

};
