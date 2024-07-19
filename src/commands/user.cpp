#include "../../includes/Server.hpp"

void Server::user(Client *client, const std::vector<std::string> params) {
    if (!client->isPassConfirmed) {
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }

    if (client->isRegistered) {
        *client << ERR_ALREADYREGISTRED_462(client->getNickname());
        return;
    }

    if (params.size() < 4) {
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }

    std::string realname = params[3];
    for (size_t i = 4; i < params.size(); ++i) {
        realname += " " + params[i];
    }
    if (realname[0] == ':') {
        realname = realname.substr(1);
    }

    client->setUserInfo(params[0], params[1], params[2], realname);
    registerClient(client);
}