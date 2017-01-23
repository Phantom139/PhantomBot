/**
    jsonToken.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _JSONTOKEN_H
#define _JSONTOKEN_H

#include "../include.h"

namespace JSON {

	//TokenType: A list of JSON Tokens
	enum TokenType {
		OBJECT_BEGIN,
		OBJECT_END,
		ARRAY_BEGIN,
		ARRAY_END,
		COMMA,
		COLON,
		STRING,
		NUMERIC,
		BOOLEAN,
		TNULL,
		EOF,
		UNKNOWN
	};
	
	//Token: A simple internal to name representation of the TokenType interface
	class Token {
		public:
			Token() : t(UNKNOWN) { }
			
			string getName() { return n; }
			TokenType getType() { return t; }
			
			void set(TokenType token) { t = token; }
			void set(string name) { n = name; }
			
			Token& operator+=(string text) {
				n += text;
				return *this;
			}
			Token& operator+=(char c) {
				n += c;
				return *this;
			}			
			
		private:
			TokenType t;
			string n;
	};

};

#endif //_JSONTOKEN_H
