#include "../includes/Server.hpp"

bool isValidNickname(const std::string &nickname);
bool isDuplicateNickname(std::map<int, Client*> clients, const std::string &nickname);

void Server::nick(Client *client, const std::string &nickname) {
    // TODO: pass 확인
    if (!client->isPassConfirmed) {
        // 451 ERR_NOTREGISTERED ":You have not registered"
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }

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
    if (isDuplicateNickname(_clients, nickname)) {
        // 433 ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"
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

bool isDuplicateNickname(std::map<int, Client*> clients, const std::string &nickname) {
    for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->second->getNickname() == nickname) {
            return true;
        }
    }
    return false;
}