/**
    pmath.h
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#ifndef _CCMD_PMATH_H
#define _CCMD_PMATH_H

#include "CustomCommands.h"

class Command_PAdd : public CustomCommand {
	public:
		/* Public Class Methods */
		//Constructor
		Command_PAdd() : CustomCommand() { }
		//Destructor
		virtual ~Command_PAdd() { }
		//Run the command
		virtual void Fire(std::string input) {
			std::string name, message;
			Lib::stripMessage(input, name, message);
			//Strip out the !padd part
			size_t argsBegin = message.find("!padd")+5;
			std::string toParse = message.substr(argsBegin, message.length());
			std::vector<std::string> terms;
			std::vector<char> token;
			token.push_back(' ');
			token.push_back(',');
			double result = 0;
			Lib::tokenizeString(toParse, token, terms);
			for(int i = 0; i < terms.size(); i++) {
				result += atoi(terms[i].c_str());
			} 
			
		}
};

#endif //_CCMD_PMATH_H
