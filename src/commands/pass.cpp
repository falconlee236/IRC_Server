#include "../../includes/Server.hpp"

void Server::pass(Client *client, const std::vector<std::string> params) {
    if (params.empty()){
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }
    if (Server::_password != params.back()){
        *client << ERR_PASSWDMISMATCH_464(client->getNickname());
        return;
    }
    client->isPassConfirmed = true;
}