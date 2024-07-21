#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"

void Server::part(Client *client, const std::vector<std::string> params) {
    if (!client->isRegistered) {
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
    if (params.empty()) {
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }

    std::vector<std::string> channels = Message::split(params[0], ',');
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
        Channel *channel = getExistingChannel(*it);
        if (channel) {
            channel->part(client);
        } else {
            *client << ERR_NOSUCHCHANNEL_403(client->getNickname(), *it);
        }
    }
}

void Channel::part(Client *client) {
    if (!isClientInChannel(client)) {
        *client << ERR_NOTONCHANNEL_442(client->getNickname(), _name);
        return;
    }

    removeClient(client);
    *this << RPL_CHANNELPART(*client, _name);
    *client << RPL_CHANNELPART(*client, _name);

    // client가 없으면 channel 삭제
    if (_clients.empty()) {
        delete this;
    }
}