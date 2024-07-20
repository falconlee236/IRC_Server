#include "../../includes/Server.hpp"

void Server::join(Client *client, const std::vector<std::string> params) {
    if (!client->isRegistered) {
        *client << ERR_ALREADYREGISTRED_462(client->getNickname());
        return;
    }

    if (params.empty()) {
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }

    std::vector<std::string> channels = Message::split(params[0], ',');
    std::vector<std::string> keys = params.size() >= 2 ? Message::split(params[1], ',') : std::vector<std::string>();

    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if (!isValidChannel(*it)) {
            *client << ERR_BADCHANMASK_476(client->getNickname(), *it);
            return;
        }

        Channel *channel = getExistingChannel(*it);
        if (channel) {
            // TODO
            // key 확인
            // _clients에 clinet 넣기
        } else {
            createChannel(*it, client);
        }
    }
}

bool Server::isValidChannel(const std::string &channel) {
    if (channel.length() < 2 || channel.size() > CHANNEL_LENGTH) {
        return false;
    }
    return (channel[0] == '#' || channel[0] == '&');
}

Channel *Server::getExistingChannel(const std::string &channel) {
    for (std::set<Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->getName() == channel) {
            return *it;
        }
    }
    return NULL;
}

void Server::createChannel(const std::string &channel_name, Client *client) {
    Channel *new_channel = new Channel(channel_name);
    _channels.insert(new_channel);
    new_channel->addClient(client);
    new_channel->addOperator(client);

    *client << RPL_CHANNELJOIN(*client, channel_name);
    *client << RPL_NAMREPLY_353(client->getNickname(), channel_name, "@" + client->getNickname());
    *client << RPL_ENDOFNAMES_366(client->getNickname(), channel_name);
}