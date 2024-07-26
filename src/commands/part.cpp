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

    std::string part_message = std::string();
    for (std::vector<std::string>::const_iterator it = params.begin() + 1; it != params.end(); ++it) {
        part_message += *it + " ";
    }
    std::vector<std::string> channels = Message::split(params[0], ',');
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
        Channel *channel = getExistingChannel(*it);
        if (channel) {
            channel->part(client, part_message);
        } else {
            *client << ERR_NOSUCHCHANNEL_403(client->getNickname(), *it);
        }
    }
}

void Channel::part(Client *client, const std::string &part_message) {
    if (!isClientInChannel(client)) {
        *client << ERR_NOTONCHANNEL_442(client->getNickname(), _name);
        return;
    }

    *this << RPL_CHANNELPART(*client, _name, part_message);
    *client << RPL_CHANNELPART(*client, _name, part_message);
    Channel::removeClient(client);

    // client가 없으면 channel 삭제
    if (_clients.empty()) {
        delete this;
    }
}