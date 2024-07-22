#include "../../includes/Server.hpp"

void Server::pass(Client *client, const std::vector<std::string> params) {
    if (params.empty())
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
    else if (Server::_password != params.back()){
        *client << ERR_PASSWDMISMATCH_464(client->getNickname());
        throw std::runtime_error("password incorrect");
    }
    else 
        client->isPassConfirmed = true;
}