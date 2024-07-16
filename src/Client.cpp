#include "../includes/Client.hpp"

Client::Client(int fd) : _socket(fd), _nickname("a") {}

Client::~Client() {
    close(_socket);
}

int Client::getSocket() const {
    return _socket;
}

const std::string& Client::getNickname() const {
    return _nickname;
}

void Client::setNickname(const std::string &nickname) {
    _nickname = nickname;
}

void Client::setUserInfo(const std::string &username, const std::string &hostname, const std::string &servername, const std::string &realname) {
    _username = username;
    _hostname = hostname;
    _servername = servername;
    _realname = realname;
}

bool Client::isRegistered() const {
    return _isRegistered;
}