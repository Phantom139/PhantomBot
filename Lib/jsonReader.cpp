/**
    jsonReader.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 16.04 LTS
**/

#include "jsonReader.h"

namespace JSON {

	jsonReader::jsonReader(string inputJSON) {
		cLine = 1;
		
		ss = new StringStream(inputJSON, inputJSON.size());
		l = new Lexer(ss);
		
		parseJSONToContents(inputJSON);
	}

	void jsonReader::parseJSONToContents(string input) {
		string tmp;
		for(int i = 0; i < input.size(); i++) {
			if(input[i] != '\n') {
				tmp += input[i];
			}
			else {
				contents.push_bach(tmp);
				tmp = "";
			}
		}
	}

};
