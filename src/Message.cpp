#include "../includes/Message.hpp"

const std::string Message::_commandList[Message::CMD_SIZE + 1] = {
    "NONE", "CAP", "PASS", 
    "NICK", "USER", "QUIT", 
    "JOIN", "PART", "TOPIC", 
    "MODE", "INVITE", "KICK", 
    "PRIVMSG", "PING"
};

Message::Message() : _cmd_type(Message::NONE), _cmd(), _params() {}

Message::Message(std::string str) : _cmd_type(Message::NONE), _cmd(), _params() {
    std::vector<std::string> tokens = splitMessage(str);
    if (!tokens.empty()) {
        _cmd_type = findCommand(tokens[0]);
        _cmd = tokens[0];
        _params.assign(tokens.begin() + 1, tokens.end());
    }
}

Message::~Message() {}

std::vector<std::string> Message::splitMessage(const std::string &str) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(str);

    while (std::getline(iss, token, ' ')) {
        // 끝에 \r 또는 \n이 오면 제거
        std::size_t endPos = token.find_last_not_of("\r\n");
        if (endPos != std::string::npos) {
            token.erase(endPos + 1);
        } else {
            token.clear();
        }
        tokens.push_back(token.substr(0, endPos + 1));
    }
    return tokens;
}

Message::e_cmd Message::findCommand(const std::string &cmd){
    std::string tmp_cmd(cmd);
    for(size_t i = 0; i <= tmp_cmd.length(); i++){
        tmp_cmd[i] = std::toupper(tmp_cmd[i]);
    }
    for(int i = 1; i <= Message::CMD_SIZE; i++) {
        if (tmp_cmd == _commandList[i]) {
            return static_cast<e_cmd>(i);
        }
    }
    return static_cast<e_cmd>(0);
}

Message::e_cmd Message::getCmdType() {
    return _cmd_type;
}

const std::string Message::getCmd() {
    return _cmd;
}

const std::vector<std::string> Message::getParams() {
    return _params;
}

Message::Message(const Message &obj) {
    _cmd_type = obj._cmd_type;
    _cmd = obj._cmd;
    _params = obj._params;
}

Message& Message::operator=(const Message &obj) {
    if (this != &obj){
        _cmd_type = obj._cmd_type;
        _cmd = obj._cmd;
        _params = obj._params;
    }
    return *this;
}