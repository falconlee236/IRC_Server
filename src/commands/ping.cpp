#include "../../includes/Server.hpp"

void Server::ping(Client *client, const std::vector<std::string> params){
    if (params.empty())
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
    else
        *client << RPL_PONG(params[0]);
}