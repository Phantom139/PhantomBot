/**
    lib.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "lib.h"

namespace Lib {

	Socket *createSocketAndConnect(UFC32 addr, U32 port) {
		Socket *s = new Socket();
		if(!s->create()) {
		    cout << "Lib::createSocketAndConnect(): Creation Failed" << endl;
		    return NULL;
		}
		if(!s->connect(addr, port)) {
		    cout << "Lib::createSocketAndConnect(): Connection Failed" << endl;
		    return NULL;        
		}
		return s;
	}

	string currentTime() {
		string currentTime = Time::fetchTimestamp();
		return currentTime;
	}
	
	const U64 fetchTime() {
		TimeVars tv;

		Time::utcTime(tv);

		unsigned long long millisecondsSinceEpoch =
    		(unsigned long long)(tv.seconds) * 1000 +
    		(unsigned long long)(tv.miliseconds) / 1000;
    		
    	return millisecondsSinceEpoch;
	}

	void writeToLog(string logLocation, string message) {
	    fstream f(logLocation.c_str(), fstream::app | fstream::out);
		string output;
		output = "[" + currentTime() + "]: " + message + "\n";
		f.write(output.c_str(), output.size());
		f.close();
	}
	
	string formatForPrint(string incoming) {
		string out = incoming;
		out.erase(remove(out.begin(), out.end(), '\r'), out.end());
		out.erase(remove(out.begin(), out.end(), '\n'), out.end());
		return out;
	}
	
	string formatChatMessage(const string message) {
		const string format = "PRIVMSG " + TwitchCommandLimit::fetchInstance().Channel() + " :" + message + "\r\n";
		return format;
	}	
	
	void stripMessage(string incoming, string &username, string &message) {
		string cName = TwitchCommandLimit::fetchInstance().Channel();
		SIZE_T nameBegin = incoming.find("display-name=")+13;
		SIZE_T nameEnd = incoming.find(";", nameBegin);
		SIZE_T messageStart = incoming.find(cName + " :") + cName.size() + 2;
		//The correct format is :NAME!, test here
		username = incoming.substr(nameBegin, (nameEnd - nameBegin));
		//Fetch the message content
		if(messageStart != string::npos) {
			for(SIZE_T i = messageStart; i < incoming.size(); i++) {
				message.push_back(incoming[i]);
			}
		}	
	}
	
	bool validateExpr(const string incoming, const string validTokens) {
		return incoming.find_first_not_of(validTokens) == string::npos;
	}
	
	void tokenizeString(const string incoming, const vector<ACHAR> tokens, queue<string> &out) {
		UFC32 str = incoming.c_str();
		do {
			UFC32 begin = str;
			for(SIZE_T i = 0; i < tokens.size(); i++) {
				while(*str != tokens[i] && *str) {
				    str++;
				}
			}
			out.push(string(begin, str));
		} while (0 != *str++);	

	}
	
	string strTrim(const string &s) {
		string::const_iterator it = s.begin();
		while (it != s.end() && isspace(*it)) {
		    it++;
		}
		string::const_reverse_iterator rit = s.rbegin();
		while (rit.base() != it && isspace(*rit)) {
		    rit++;
		}
		return string(it, rit.base());
	}	

};
