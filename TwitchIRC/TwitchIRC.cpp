/**
    TwitchIRC.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
    Built on Ubuntu 14.04.10 LTS
**/

#include "TwitchIRC.h"

/**
    TwitchIRC Class
**/

TwitchIRC::TwitchIRC(const std::string nick, const std::string usr, const std::string pass, const std::string addr, unsigned int port, const std::string channel) : _connectedChannel(channel), _socketObj(NULL) {
    cout << "IRCClient: Establishing" << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Establishing TwitchIRC Instance");
    //Create the socket
    _socketObj = Lib::createSocketAndConnect(addr, port);
    if(!_socketObj) {
        cout << "Failed to establish connection to " << addr.c_str() << endl;
        Lib::writeToLog("PhantomBotLog.txt", "{C++} Failed to connect to " + addr + ".");
        return;
    }
    cout << "Initializing Command Instances" << endl;
    //Init the command limit instance...
    TwitchCommandLimit::fetchInstance().Init(_socketObj, channel);
    ChatCommandDecs::fetchInstance().init();
    cout << "Creating Command Interfaces..." << endl;
    //Construct the login token
    cout << "IRCClient: Establishing login token" << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Establishing TwitchIRC Login Token");
    const std::string pS = string("PASS " + pass + "\r\n");
    const std::string nS = string("NICK " + nick + "\r\n");
    const std::string uS = string("USER " + usr + "\r\n");
    //Password must be sent first, then our information
    if(pS.size()) {
        TwitchCommandLimit::fetchInstance().PushCommand(pS);
    }
    TwitchCommandLimit::fetchInstance().PushCommand(nS);
    TwitchCommandLimit::fetchInstance().PushCommand(uS);
    //Wait for the welcome reply...
    std::string response;
    fetchServerMessage(response);
    if(response.find("Welcome") == string::npos) {
        //We failed...
        cout << "BOT: Failed to connect to TwitchIRC" << endl << endl << response.c_str() << endl << endl;
        Lib::writeToLog("PhantomBotLog.txt", "{Twitch} We did not recieve a welcome message");
        CloseSocket();
    }
    else {
        //Enable advanced commnads
        const std::string aCS = string("CAP REQ :twitch.tv/commands\r\nCAP REQ :twitch.tv/membership\r\nCAP REQ :twitch.tv/tags\r\n");
        TwitchCommandLimit::fetchInstance().PushCommand(aCS);
        Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Connected to TwitchIRC, connecting to channel '#" + channel + "'.");
        //And finally... connect to the channel
        const std::string cS = string("JOIN " + channel + "\r\n");
        TwitchCommandLimit::fetchInstance().PushCommand(cS);
        //Send a intro message to init stuff...
        SendChatMessage("PhantomBot Now Connected to channel...");
    }
}

TwitchIRC::~TwitchIRC() {
    Lib::writeToLog("PhantomBotLog.txt", "{C++} Calling ~TwitchIRC(), closing program...\n\n");
    CloseSocket();
}

void TwitchIRC::Update() {
    std::string response;
    fetchServerMessage(response);
    if(response.size()) {
        //Process messages based on the content
        TwitchCommand *cmd;
        if(response.find("PRIVMSG") != string::npos) {
        	TwitchPrivMsg::fetchInstance().Process(response);
        }
        else if(response.find("PING") != string::npos) {
        	TwitchPing::fetchInstance().Process(response);       	
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

bool TwitchIRC::SendChatMessage(const std::string message) {
	if(!SocketActive()) {
		return false;
	}
	std::cout << "BOT: Sending Message: " << Lib::formatForPrint(message).c_str() << "..." << std::endl;
	Lib::writeToLog("PhantomBotLog.txt", "{Twitch} Sending Message " + Lib::formatForPrint(message) + "...");
	const std::string format = "PRIVMSG " + _connectedChannel + " :" + message + "\r\n";
	//Add it to the queue
	TwitchCommandLimit::fetchInstance().AddCommand(format);
}

bool TwitchIRC::fetchServerMessage(std::string &message) {
	while(SocketActive()) {
		std::string incoming;
		int result = _socketObj->Recieve(incoming);
		if(result <= 0) {
		    //Something went wrong TO-DO: test for timeouts, etc...
		    std::cout << "An error occurred when recieving a server message, errno: " << errno << std::endl;
		    return false;
		}
		//check for /r/n
		message += incoming;
		if(message.size() > 1 && message[message.size() - 2] == '\r' && message[message.size() - 1] == '\n') {
			return true;
		}
		//Too big...
		if(message.size() > LIMIT_16) {
			std::cout << "Endless buffer error, closing socket" << std::endl;
			CloseSocket();
		}
	}
	return false;
}
