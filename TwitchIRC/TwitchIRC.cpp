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
    //Create the buffer
    buffer = new ACHAR[_MAXRECV];
    //Create the socket
    _socketObj = Lib::createSocketAndConnect(addr, port);
    if(!_socketObj) {
        cout << "Failed to establish connection to " << addr << endl;
        Lib::writeToLog("PhantomBotLog.txt", "{C++} Failed to connect to " + string(addr)+ ".");
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
    const string pS = string("PASS " + string(pass) + "\r\n");
    const string nS = string("NICK " + string(nick) + "\r\n");
    const string uS = string("USER " + string(usr) + "\r\n");
    //Password must be sent first, then our information
    if(pS.size()) {
        TwitchCommandLimit::fetchInstance().SendCommand(pS);
    }
    TwitchCommandLimit::fetchInstance().SendCommand(nS);
    TwitchCommandLimit::fetchInstance().SendCommand(uS);
    //Wait for the welcome reply...
    fetchServerMessage();
    if(response.find("Welcome") == string::npos) {
        //We failed...
        cout << "BOT: Failed to connect to TwitchIRC" << endl << endl << response.c_str() << endl << endl;
        Lib::writeToLog("PhantomBotLog.txt", "{Twitch} We did not recieve a welcome message");
        CloseSocket();
    }
    else {
		//Set the socket to non-blocking mode to allow the program to continue execution
		_socketObj->setNonBlocking();
        //Enable advanced commnads
        const string aCS1 = string("CAP REQ :twitch.tv/commands\r\n");
        const string aCS2 = string("CAP REQ :twitch.tv/membership\r\n");
        const string aCS3 = string("CAP REQ :twitch.tv/tags\r\n");
        TwitchCommandLimit::fetchInstance().SendCommand(aCS1);
        TwitchCommandLimit::fetchInstance().SendCommand(aCS2);
        TwitchCommandLimit::fetchInstance().SendCommand(aCS3);
        Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Connected to TwitchIRC, connecting to channel '#" + string(channel) + "'.");
        //And finally... connect to the channel
        const string cS = string("JOIN " + string(channel) + "\r\n");
        TwitchCommandLimit::fetchInstance().SendCommand(cS);
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
    fetchServerMessage();
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
        	//cout << "Got unknown response: " << response << endl;
        	//Lib::writeToLog("PhantomBotLog.txt", "{Twitch} UIID Response '" + response + "'.");
        }
    }
}

void TwitchIRC::CloseSocket() {
	if(_socketObj) {
        _socketObj->close();
    }   	
}

bool TwitchIRC::SocketActive() {
	if(_socketObj) {
		return _socketObj->isValidSocket();
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
	return true;
}

bool TwitchIRC::ProcessConsoleCommand(UFC32 input) {
	//Big Time To-Do Here :P
	return true;
}

bool TwitchIRC::fetchServerMessage() {
    response = "";
	while (SocketActive()) {
		//Get some data...
		S32 bytesRead;
		SocketCode rc = _socketObj->receive(buffer, _MAXRECV, &bytesRead);
		if (rc == SocketCode::Disconnected) {
			cout << "Server has closed socket connection, abort..." << endl;
			return false;
		}
		else if (rc == SocketCode::RecieveError) {
			//Socket classes are programmed to automatically push the error, no need to repeat here.
			return false;
		}
		else if(rc == SocketCode::NoError) {
			if (bytesRead > 0) {
				response += string((ACHAR *)buffer);
				fill_n(buffer, sizeof(buffer), NULL);
				//Check if the server sent it all in one go
				if (response.size() > 1 && response[response.size() - 2] == '\r' && response[response.size() - 1] == '\n') {
					return true;
				}
			}
			else {
				if (bytesRead < 0) {
					//What have you done????
					cout << "You have caused some kind of voo-doo magic (" << errno << ") to occur, please stop..." << endl;
					response = "";
					return false;
				}
				//End of the buffer!
				return true;
			}
		}
	}
	return false;
}
