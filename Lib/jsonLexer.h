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
			virtual ACHAR peek() = 0;
			//Obtain next charachter
			virtual ACHAR get() = 0;
			//Move forward in queue
			virtual void moveBack() = 0;
			//Test next charachters in stream to see if they match the test variable
			virtual bool nextCharsMatch(UFC32 test) = 0;
			//Current line number
			virtual S32 lNum() const = 0;
			//Current charachter position
			virtual S32 curPos() const = 0;
	};
	
	//String information to JSON source
	class StringStream : public Stream { 
		public:
			StringStream(UFC32 jsonIn, SIZE_T bufferSize) :
				strStart(jsonIn), strCPos(jsonIn), strEnd(jsonIn + bufferSize),
				cLine(1), cPos(1) {
				
			}
		
			virtual ACHAR peek();			
			virtual ACHAR get();
			virtual void moveBack();
			virtual bool nextCharsMatch(UFC32 test);
			virtual S32 lNum() const;
			virtual S32 curPos() const;
		
		private:
			void updatePosition(ACHAR tChar);
		
			UFC32 strStart;
			UFC32 strCPos;
			UFC32 strEnd;
			S32 cLine;
			S32 cPos;
	};
	
	//Toolset which tokenizes individual string elements
	class Lexer {
		public:
			Lexer(Stream &src) : srcStream(&src) { }
			Token readNext();
			
			S32 lNum() const;
			S32 curPos() const;
		
		private:
			U8 readFromHex(ACHAR c);
			Token readFromString(ACHAR c);
			Token readFromNumber(ACHAR c);
			bool charIsSign(ACHAR c);
			
			Stream *srcStream;
	};
	
	/*
	Stream Utilities
	*/
	inline void conditionalException(Stream *src, bool throwCondition, string msg);
	inline void conditionalException(bool throwCondition, string msg);

};

#endif //_JSONLEXER_H
