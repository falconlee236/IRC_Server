#include "../includes/Server.hpp"

bool isValidNickname(const std::string &nickname);

void Server::nick(Client *client, const std::string &nickname) {
    // TODO: pass 확인

    if (nickname.empty()) {
        // 431 ERR_NONICKNAMEGIVEN ":No nickname given"
        std::string response = ERR_NONICKNAMEGIVEN_431(client->getNickname());
        send(client->getSocket(), response.c_str(), response.size(), 0);
        return;
    }

    if (!isValidNickname(nickname)) {
        // 432 ERR_ERRONEUSNICKNAME "<nick> :Erroneus nickname"
        std::string response = ERR_ERRONEUSNICKNAME_432(client->getNickname(), nickname);
        send(client->getSocket(), response.c_str(), response.size(), 0);
        return;
    }

    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nickname) {
            // 433 ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"
            std::string response = ERR_NICKNAMEINUSE_433(client->getNickname(), nickname);
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

    if ('0' <= nickname[0] && nickname[0] <= '9') {
        return false;
    }

    for (std::string::const_iterator it = nickname.begin(); it != nickname.end(); ++it) {
        if (!(isalnum(*it) || '_')) {
            return false;
        }
    }
    return true;
}