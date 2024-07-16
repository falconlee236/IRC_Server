#include "../../includes/Server.hpp"

void Server::nick(Client *client, const std::vector<std::string> params) {
    // TODO: pass 확인
    // if (!client->isPassConfirmed) {
    //     // 451 ERR_NOTREGISTERED ":You have not registered"
    //     *client << ERR_NOTREGISTERED_451(client->getNickname());
    //     return;
    // }

    if (params.empty()) {
        *client << ERR_NONICKNAMEGIVEN_431(client->getNickname());
        return;
    }

    std::string nickname = params[0];
    if (!isValidNickname(nickname)) {
        *client << ERR_ERRONEUSNICKNAME_432(client->getNickname(), nickname);
        return;
    }
    if (isDuplicateNickname(nickname)) {
        *client << ERR_NICKNAMEINUSE_433(client->getNickname(), nickname);
        return;
    }

    // 기존에 register 되어 있었던 client인 경우
    if (client->isRegistered()) {
        std::string old_nickname = client->getNickname();
        client->setNickname(nickname);
        *client << RPL_NICKNAMECHANGE(client->getNickname(), old_nickname);
    } else {
        client->setNickname(nickname);
        // TODO: register
    }
}

bool Server::isValidNickname(const std::string &nickname) {
    if (nickname.length() > 9) {
        return false;
    }
    if ('0' <= nickname[0] && nickname[0] <= '9') {
        return false;
    }
    for (std::string::const_iterator it = nickname.begin(); it != nickname.end(); it++) {
        if (!isalnum(*it) && *it != '_') {
            return false;
        }
    }
    return true;
}

bool Server::isDuplicateNickname(const std::string &nickname) {
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->second->getNickname() == nickname) {
            return true;
        }
    }
    return false;
}