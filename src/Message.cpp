#include "../includes/Message.hpp"

const std::string Message::_commandList[Message::CMD_SIZE + 1] = {
	"NONE", "CAP", "PASS", 
	"NICK", "USER", "QUIT", 
	"JOIN", "PART", "TOPIC", 
	"MODE", "INVITE", "KICK", 
	"PRIVMSG", "PING"
};


std::vector<std::string> Message::splitN(const std::string& str, char delimiter, size_t n) {
    std::vector<std::string> tokens;
    std::istringstream stream(str);
    std::string token;
    size_t count = 0;

    while (std::getline(stream, token, delimiter) && count < n - 1) {
        tokens.push_back(token);
        count++;
    }
    // Add the remaining part of the string
    if (stream) {
        std::string remaining((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        if (!token.empty())
            remaining = token + delimiter + remaining;
        tokens.push_back(remaining);
    }
    return tokens;
}

Message::e_cmd Message::findCommand(const std::string cmd_str){
	for(int i = 1; i <= Message::CMD_SIZE; i++){
		if (cmd_str == _commandList[i]) return static_cast<e_cmd>(i);
	}
	return static_cast<e_cmd>(0);
}


Message::Message(std::string str){
	std::vector<std::string> ans = splitN(str, ' ', 2);
	_cmd_type = findCommand(ans[0]);
	_params = ans.size() == 1 ? "" : ans[1];
}

Message::e_cmd Message::getCommand(void){return _cmd_type;}
const std::string Message::getParams(void){return _params;}
Message::Message(void) : _cmd_type(Message::NONE), _params("") {}
Message::~Message(){}
Message::Message(const Message& obj){
	_cmd_type = obj._cmd_type;
	_params = obj._params;
}
Message& Message::operator= (const Message& obj){
	if (this != &obj){
		_cmd_type = obj._cmd_type;
		_params = obj._params;
	}
	return *this;
}