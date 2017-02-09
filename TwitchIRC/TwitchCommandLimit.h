/**
    TwitchIRC.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _TWITCHCOMMANDLIMIT_H
#define _TWITCHCOMMANDLIMIT_H

#include "../include.h"
#include "../Lib/lib.h"
#include "Admin.h"

/*
TwitchCommandLimit Struct
Class instance used to protect the bot from going over the command limit
*/
struct TwitchCommandLimit {
    /* Class Enumerations */
    enum TwitchLimits {
        //How many commands can we send in a 30 second period
        COMMAND_LIMIT_NORMAL = 20,
        //If we're a op/mod, how many?
        COMMAND_LIMIT_OPMOD = 100,
    };

    /* Methods */
    //Constructor
    TwitchCommandLimit();
    //Init Instance
    void Init(Socket *sO, string cName);
    //Process the USERSTATE message
    void ProcessUserState(const string command);
    //Add a command to the process queue
    void AddCommand(const string command);
    //Push a command through the pipe.
    void PushCommand(const string command);
    //Update, called by TwitchIRC on it's update cycle
    void Update();
    //Return the name of the active channel
    const string Channel() const;
    //Wrapper to send with error check
    void SendCommand(const string command);
    //Debug mode on?
    const bool DebugMode() const;
    //Admin Only mode?
    const bool AdminOnlyMode() const;
    //Set Debug Mode
    void setDebugMode(bool flag = false) { debugMode = flag; }
    //Set Admin Mode
    void setAdminMode(bool flag = false) { adminOnlyMode = flag; }
    //Fetch singleton instance
    static TwitchCommandLimit &fetchInstance();

    private:
        /* Members */
		//The update thread
		thread *updateThread;
        //The name of the channel
        string channel;
		//The queue of force commands
		queue<string> forcedCommands;
        //The Queue of commands that will be processed
        queue<string> normalCommands;
        //How many commands have we sent from the last 30s update?
        S32 currentSendCount;
        //Do we have mod status?
        bool isModOrOp;
        //The timeval at the time of the currentSendCount initiation
        TimeVars curTVal;
        //The timeval at the time of the forcedSendCount initiation
        TimeVars curFVal;
        //Attached socket instance
        Socket *aSock;
        //DEBUG MODE FLAG
        bool debugMode;
        //Admin only mode
        bool adminOnlyMode;
};

#endif //_TWITCHCOMMANDLIMIT_H
