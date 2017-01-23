/**
    jsonReader.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _JSONREADER_H
#define _JSONREADER_H

#include "../include.h"
#include "jsonLexer.h"

namespace JSON {

	//jsonReader: A simple interface for parsing JSON files
	class jsonReader {
		public:
			jsonReader(string inputJSON);
			~jsonReader();
			
			void nextObject();
			void previousObject();
			void nextArray();
			void previousArray();
			bool readKey(string name);
			int readKey(string name);
			string readKey(string name);
			double readKey(string name);

			int curLine() const;

		private:
			void parseJSONToContents(string input);
		
		
			int cLine;
		
			vector<string> contents;
			StringStream *ss;
			Lexer *l;
	
	};

};

#endif //_JSONREADER_H
