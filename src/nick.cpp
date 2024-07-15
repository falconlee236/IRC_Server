#include "../includes/Server.hpp"

bool isValidNickname(const std::string &nickname);

void Server::nick(Client *client, const std::string &nickname) {
    // TODO: pass 확인

    if (nickname.empty()) {
        // TODO: 431 ERR_NONICKNAMEGIVEN
        std::string response = "431 :No nickname given\r\n";
        send(client->getSocket(), response.c_str(), response.size(), 0);
        return;
    }

    if (!isValidNickname(nickname)) {
        // TODO: 432 ERR_ERRONEUSNICKNAME
        std::string response = "432 " + client->getNickname() + ":Erroneus nickname\r\n";
        send(client->getSocket(), response.c_str(), response.size(), 0);
        return;
    }

    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nickname) {
            // TODO: 433 ERR_NICKNAMEINUSE
            std::string response = "433 " + nickname + " :Nickname is already in use\r\n";
            send(client->getSocket(), response.c_str(), response.size(), 0);
            return;
        }
    }

    std::string old_nickname = client->getNickname();
    client->setNickname(nickname);
    // std::string response = ":" + old_nickname + " NICK " + client->getNickname() + "\r\n";
}

bool isValidNickname(const std::string &nickname) {
    if (nickname.length() > 9) {
        return false;
    }
    if ('0' <= nickname[0] || nickname[0] <= '9') {
        return false;
    }

    for (std::string::const_iterator it = nickname.begin(); it != nickname.end(); ++it) {
        if (!(isalnum(*it) || isspecial(*it))) {
            return false;
        }
    }
    return true;
}