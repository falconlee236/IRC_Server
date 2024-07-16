#include "../includes/Server.hpp"

void Server::user(Client *client, const std::string &user_info) {
    // TODO: pass 확인

    if (client->isRegistered()) {
        // TODO: 462 ERR_ALREADYREGISTRED
    }

    std::istringstream iss(user_info);
    std::string username, hostname, servername, realname;
    if (!(iss >> username >> hostname >> servername)) {
        // TODO: 461 ERR_NEEDMOREPARAMS
        std::string response = "461 USER :Not enough parameters\r\n";
        send(client->getSocket(), response.c_str(), response.size(), 0);
        return;
    }

    std::getline(iss, realname);
    if (realname[0] == ':') {
        realname = realname.substr(1);
    }

    client->setUserInfo(username, hostname, servername, realname);
}