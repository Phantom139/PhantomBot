/**
    lib.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _LIB_H
#define _LIB_H

#include "../include.h"
#include "../TwitchIRC/TwitchCommandLimit.h"

#define LIMIT_16 ((signed short)0x7FFF)

/*
Lib Class
 Collection of support and utility functions
*/
namespace Lib {
    //Create a socket and connect to specified instance
    Socket *createSocketAndConnect(UFC32 addr, U32 port);
    //Fetch the current timestring
    string currentTime();
    //Fetch UTC time, unsigned integer
    const U64 fetchTime();
    //Write a log line
    void writeToLog(string logLocation, string message);
    //Format an incoming command line to strip out /r/n for proper output
    string formatForPrint(string incoming);
    //Format a chat message
    string formatChatMessage(const string message);
    //Strip the contents of a message into username / message
    void stripMessage(string incoming, string &username, string &message);
    //Validate an expression
    bool validateExpr(const string incoming, const string validTokens);
    //Tokenize a string based on input parameters
    void tokenizeString(const string incoming, const vector<ACHAR> tokens, queue<string> &out);
    //Trim spaces from a string
    string strTrim(const string &s);
};


#endif //_LIB_H
