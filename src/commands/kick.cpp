#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"

void Server::kick(Client *client, const std::vector<std::string> params) {
    if (!client->isRegistered) {
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
    if (params.size() < 2) {
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }

    Channel *channel = getExistingChannel(params[0]);
    if (!channel) {
        *client << ERR_NOSUCHCHANNEL_403(client->getNickname(), params[0]);
        return;
    }

    std::vector<std::string> users = Message::split(params[1], ',');
    std::string kick_message = std::string();
    for (std::vector<std::string>::const_iterator it = params.begin() + 2; it != params.end(); ++it) {
        kick_message += *it + " ";
    }
    channel->kick(client, users, kick_message);
}

void Channel::kick(Client *client, const std::vector<std::string> &users, const std::string &message) {
    if (!isClientInChannel(client)) {
        *client << ERR_NOTONCHANNEL_442(client->getNickname(), _name);
        return;
    }
    if (!isOperator(client)) {
        *client << ERR_CHANOPRIVSNEEDED_482(client->getNickname(), _name);
        return;
    }

    for (std::vector<std::string>::const_iterator it = users.begin(); it != users.end(); ++it) {
        std::map<std::string, Client*>::iterator user = _clients_map.find(*it);
        if (user != _clients_map.end()) {
            *this << RPL_CHANNELKICK(*client, _name, *it, message);
            Channel::removeClient(user->second);
        } else {
            *client << ERR_USERNOTINCHANNEL_441(client->getNickname(), *it, _name);
        }
    }
}