/**
    TwitchIRC.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchIRC.h"

/**
    TwitchIRC Class
**/

TwitchIRC::TwitchIRC(UFC32 nick, UFC32 usr, UFC32 pass, UFC32 addr, U32 port, UFC32 channel) :
	_connectedChannel(channel), serverAddr(), serverPort(0), _socketObj(NULL), autoping_thread(NULL) {
    cout << "IRCClient: Establishing" << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Establishing TwitchIRC Instance");
    //Create the socket
    _socketObj = Lib::createSocketAndConnect(addr, port);
    if(!_socketObj) {
        cout << "Failed to establish connection to " << addr << endl;
        Lib::writeToLog("PhantomBotLog.txt", "{C++} Failed to connect to " + addr + ".");
        return;
    }
    serverAddr = addr;
    serverPort = port;
    cout << "Initializing Command Instances" << endl;
    //Init the command limit instance...
    TwitchCommandLimit::fetchInstance().Init(_socketObj, channel);
    ChatCommandDecs::fetchInstance().init();
    cout << "Creating Command Interfaces..." << endl;
    //Construct the login token
    cout << "IRCClient: Establishing login token" << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Establishing TwitchIRC Login Token");
    const string pS = string("PASS " + pass + "\r\n");
    const string nS = string("NICK " + nick + "\r\n");
    const string uS = string("USER " + usr + "\r\n");
    //Password must be sent first, then our information
    if(pS.size()) {
        TwitchCommandLimit::fetchInstance().PushCommand(pS);
    }
    TwitchCommandLimit::fetchInstance().PushCommand(nS);
    TwitchCommandLimit::fetchInstance().PushCommand(uS);
    //Wait for the welcome reply...
    string response;
    fetchServerMessage(response);
    if(response.find("Welcome") == string::npos) {
        //We failed...
        cout << "BOT: Failed to connect to TwitchIRC" << endl << endl << response.c_str() << endl << endl;
        Lib::writeToLog("PhantomBotLog.txt", "{Twitch} We did not recieve a welcome message");
        CloseSocket();
    }
    else {
        //Enable advanced commnads
        const string aCS1 = string("CAP REQ :twitch.tv/commands\r\n");
        const string aCS2 = string("CAP REQ :twitch.tv/membership\r\n");
        const string aCS3 = string("CAP REQ :twitch.tv/tags\r\n");
        TwitchCommandLimit::fetchInstance().PushCommand(aCS1);
        TwitchCommandLimit::fetchInstance().PushCommand(aCS2);
        TwitchCommandLimit::fetchInstance().PushCommand(aCS3);
        Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Connected to TwitchIRC, connecting to channel '#" + channel + "'.");
        //And finally... connect to the channel
        const string cS = string("JOIN " + channel + "\r\n");
        TwitchCommandLimit::fetchInstance().PushCommand(cS);
        //Send a intro message to init stuff...
        SendChatMessage("PhantomBot Now Connected to channel...");
        //Set up AutoPing command
        autoping_thread = new thread(&TwitchIRC::AutoPing, this);
    }
}

TwitchIRC::~TwitchIRC() {
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Calling ~TwitchIRC(), closing program...\n\n");
    CloseSocket();
}

void TwitchIRC::Update() {
    string response;
    fetchServerMessage(response);
    //cout << "Server: " << response << endl;
    if(response.size()) {
        //Process messages based on the content
        TwitchCommand *cmd;
        if(response.find("PRIVMSG") != string::npos) {
        	TwitchPrivMsg::fetchInstance().Process(response);
        }
        else if(response.find("PING") != string::npos) {
        	TwitchPing::fetchInstance().Process(response);       	
        }
        else if(response.find("PONG") != string::npos) {
        	cout << "BOT: Server connection confirmed..." << endl;
        }
        else if(response.find("USERSTATE") != string::npos) {
        	TwitchUserState::fetchInstance().Process(response);         	
        }    
        else {
        	cout << "Got unknown response: " << Lib::formatForPrint(response).c_str() << endl;
        	Lib::writeToLog("PhantomBotLog.txt", "{Twitch} UIID Response '" + Lib::formatForPrint(response) + "'.");
        }
    }
    //Update the command process
    TwitchCommandLimit::fetchInstance().Update();
}

void TwitchIRC::CloseSocket() {
	if(_socketObj) {
        _socketObj->Close();
    }   	
}

bool TwitchIRC::SocketActive() {
	if(_socketObj) {
		return _socketObj->IsValid();
	}
	return false;
}

void TwitchIRC::AutoPing() {
	cout << "BOT: Begin AutoPing Routine" << endl;
	while(SocketActive()) {
		cout << "BOT: Running AutoPing routine to persist connection..." << endl;
		const string command = "PING :tmi.twitch.tv\r\n";
		TwitchCommandLimit::fetchInstance().PushCommand(command);	
		this_thread::sleep_for(chrono::milliseconds(PING_INTERVAL));
	}
	autoping_thread->join();
}

bool TwitchIRC::SendChatMessage(UFC32 message) {
	if(!SocketActive()) {
		return false;
	}
	cout << "BOT: Sending Message: " << Lib::formatForPrint(message).c_str() << "..." << endl;
	Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Sending Message " + Lib::formatForPrint(message) + "...");
	const string format = "PRIVMSG " + _connectedChannel + " :" + message + "\r\n";
	//Add it to the queue
	TwitchCommandLimit::fetchInstance().AddCommand(format);
}

bool TwitchIRC::fetchServerMessage(string &message) {
	while(SocketActive()) {
		string incoming;
		S32 result = _socketObj->Recieve(incoming);
		if(result <= 0) {
		    if(errno == 0) {
		    	//Socket has been closed, re-establish
		    	cout << "Server has closed socket connection, attempting to re-establish" << endl;
				_socketObj = Lib::createSocketAndConnect(serverAddr, serverPort);
				if(!_socketObj) {
					cout << "Failed to establish connection to " << serverAddr.c_str() << endl;
					Lib::writeToLog("PhantomBotLog.txt", "{C++} Failed to connect to " + serverAddr + ".");
					return false;
				}	
				cout << "Reconnection Completed..." << endl;
				return fetchServerMessage(message);	    	
		    }
		    else {
		    	cout << "An error occurred when recieving a server message, errno: " << errno << endl;
		    	return false;
		    }
		}
		//check for /r/n
		message += incoming;
		if(message.size() > 1 && message[message.size() - 2] == '\r' && message[message.size() - 1] == '\n') {
			return true;
		}
		//Too big...
		if(message.size() > LIMIT_16) {
			cout << "Endless buffer error, closing socket" << endl;
			CloseSocket();
		}
	}
	return false;
}
