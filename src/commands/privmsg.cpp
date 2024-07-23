#include "../../includes/Server.hpp"

void Server::privmsg(Client *client, const std::vector<std::string> params) {
    if (!client->isRegistered) {
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
    if (params.size() < 2) {
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }

    std::vector<std::string> receivers = Message::split(params[0], ',');
    std::string message = std::string();
    for (std::vector<std::string>::const_iterator it = params.begin() + 1; it != params.end(); ++it) {
        message += *it + " ";
    }

    for (std::vector<std::string>::iterator it = receivers.begin(); it != receivers.end(); ++it) {
        if (isValidChannel(*it)) {
            Channel *channel = getExistingChannel(*it);
            if (channel) {
                // TODO: channel->privmsg(client, message);
            } else {
                *client << ERR_NOSUCHCHANNEL_403(client->getNickname(), *it);
            }
        } else {
            Client *target = getClientbyNickname(*it);
            if (target) {
                // TODO
            } else {
                *client << ERR_NOSUCHNICK_401(client->getNickname(), *it);
            }
        }
    }
}