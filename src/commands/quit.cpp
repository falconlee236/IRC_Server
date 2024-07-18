#include "../../includes/Server.hpp"

void Server::quit(Client *client, const std::vector<std::string> params){
    /*
    //TODO - 지금은 welcome message가 되어야지 (즉 모든 정보가 입력되어야)
    quit가 가능 그거 테스트해야함
    */
    if (!client->isRegistered())
        *client << ERR_NOTREGISTERED_451(client->getNickname());
    else {
        //NOTE - default = client name
        std::string msg = params.empty() ? client->getNickname() : params[0];
        //TODO - channel이 있다면 channel도 삭제해야함.
        *client << msg + "\r\n";
        *client >> client->getSocket();
        Server::removeClient(client->getSocket());
    }
}