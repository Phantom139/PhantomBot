/**
    jsonLexer.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _JSONLEXER_H
#define _JSONLEXER_H

#include "../include.h"
#include "jsonToken.h"

namespace JSON {

	//Generic interface for types of input sources from which JSON is read
	class Stream {
		public:
			virtual ~Stream() { }
			
			//Peek next charachter
			virtual char peek() = 0;
			//Obtain next charachter
			virtual char get() = 0;
			//Move forward in queue
			virtual void moveBack() = 0;
			//Test next charachters in stream to see if they match the test variable
			virtual bool nextCharsMatch(const char *test) = 0;
			//Current line number
			virtual int lNum() const = 0;
			//Current charachter position
			virtual int curPos() const = 0;
	};
	
	//String information to JSON source
	class StringStream : public Stream { 
		public:
			StringStream(const char *jsonIn, size_t bufferSize) :
				strStart(jsonIn), strCPos(jsonIn), strEnd(jsonIn + bufferSize),
				cLine(1), cPos(1) {
				
			}
		
			virtual char peek();			
			virtual char get();
			virtual void moveBack();
			virtual bool nextCharsMatch(const char *test);
			virtual int lNum() const;
			virtual int curPos() const;
		
		private:
			void updatePosition(char tChar);
		
			const char *strStart;
			const char *strCPos;
			const char *strEnd;
			int cLine;
			int cPos;
	};
	
	//Toolset which tokenizes individual string elements
	class Lexer {
		public:
			Lexer(Stream &src) : srcStream(&src) { }
			Token readNext();
			
			int lNum() const;
			int curPos() const;
		
		private:
			uint8_t readFromHex(char c);
			Token readFromString(char c);
			Token readFromNumber(char c);
			bool charIsSign(char c);
			
			Stream *srcStream;
	};
	
	/*
	Stream Utilities
	*/
	inline void conditionalException(Stream *src, bool throwCondition, string msg);
	inline void conditionalException(bool throwCondition, string msg);

};

#endif //_JSONLEXER_H
