#include "../includes/Server.hpp"

bool isValidNickname(const std::string &nickname);

void Server::nick(Client *client, const std::string &nickname) {
    // TODO: pass 확인

    if (nickname.empty()) {
        // 431 ERR_NONICKNAMEGIVEN ":No nickname given"
        *client << ERR_NONICKNAMEGIVEN_431(client->getNickname());
        return;
    }

    if (!isValidNickname(nickname)) {
        // 432 ERR_ERRONEUSNICKNAME "<nick> :Erroneus nickname"
        *client << ERR_ERRONEUSNICKNAME_432(client->getNickname(), nickname);
        return;
    }

    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nickname) {
            // 433 ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"
            *client << ERR_NICKNAMEINUSE_433(client->getNickname(), nickname);
            return;
        }
    }

    // TODO: 기존에 register되어 있었던 client인 경우
    std::string old_nickname = client->getNickname();
    client->setNickname(nickname);
    *client << RPL_NICKNAMECHANGE(client->getNickname(), old_nickname);
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