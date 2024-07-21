#include "../../includes/Server.hpp"

void Server::quit(Client *client, const std::vector<std::string> params){
    if (!client->isRegistered)
        *client << ERR_NOTREGISTERED_451(client->getNickname());
    else {
        std::string msg = params.empty() ? client->getNickname() : params[0];
        for (std::set<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it){
            if ((*it)->isClientInChannel(client)){
                (*it)->removeClient(client);
                // client가 없으면 channel 삭제
                if ((*it)->getClientNumber() == 0){
                    delete (*it);
                }
            }
        }
        *client << msg + "\r\n";
        *client >> client->getSocket();
        Server::removeClient(client->getSocket());
    }
}