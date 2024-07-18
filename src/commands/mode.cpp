#include "../../includes/Server.hpp"

void Server::mode(Client *client, const std::vector<std::string> params){
    if (!client->isRegistered()){
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
}