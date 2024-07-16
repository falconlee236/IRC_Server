#include "../includes/Client.hpp"

Client::Client(int fd) : _socket(fd), _nickname("nick") {}

Client::~Client() {
    close(_socket);
}

int Client::getSocket() const {
    return _socket;
}

const std::string& Client::getNickname() const {
    return _nickname;
}
void Client::setNickname(const std::string& nickname) {
    _nickname = nickname;
}