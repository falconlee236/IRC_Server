#include "../../includes/Server.hpp"

void Server::quit(Client *client, const std::vector<std::string> params){
    if (!client->isRegistered())
        *client << ERR_NOTREGISTERED_451(client->getNickname());
    else {
        //NOTE - default = client name
        std::string msg = params.empty() ? client->getNickname() : params[0];
        //TODO - channel이 있다면 channel도 삭제해야함.
        *client << msg;
        Server::removeClient(client->getSocket());
    }
}