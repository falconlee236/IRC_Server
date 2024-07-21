#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"

void Server::join(Client *client, const std::vector<std::string> params) {
    if (!client->isRegistered) {
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
    if (params.empty()) {
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }

    std::vector<std::string> channels = Message::split(params[0], ',');
    std::vector<std::string> keys = params.size() >= 2 ? Message::split(params[1], ',') : std::vector<std::string>();

    std::vector<std::string>::iterator keyIt = keys.begin();
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if (!isValidChannel(*it)) {
            *client << ERR_BADCHANMASK_476(client->getNickname(), *it);
            return;
        }

        Channel *channel = getExistingChannel(*it);
        if (channel) {
            channel->join(client, keyIt != keys.end() ? *keyIt : std::string());
        } else {
            createChannel(*it, client);
        }

        if (keyIt != keys.end()) {
            ++keyIt;
        }
    }
}

void Channel::join(Client *client, const std::string &key) {
    if (isClientInChannel(client)) {
        *client << ERR_USERONCHANNEL_443(client->getNickname(), _name);
        return;
    }
    // TODO: +l 모드에서 설정한 max 값 확인 (Channel에 max 값 저장하는 변수 추가해야 함)
    // if (isModeSet(SET_USER_LIMIT) && _clients.size() >= _max_clients) {
    //     *client << ERR_CHANNELISFULL_471(client->getNickname(), _name);
    //     return;
    // } 
    if (isModeSet(INVITE_ONLY) && _guests.find(client) == _guests.end()) {
        *client << ERR_INVITEONLYCHAN_473(client->getNickname(), _name);
        return;
    }
    if (isModeSet(SET_KEY) && key != _key) {
        *client << ERR_BADCHANNELKEY_475(client->getNickname(), _name);
        return;
    }

    addClient(client);
    _guests.erase(client);
    _guests_map.erase(client->getNickname());

    std::string user_list;
    for (std::set<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (_operators.find(*it) != _operators.end()) {
            user_list += "@" + (*it)->getNickname();
        } else {
            user_list += " " + (*it)->getNickname();
        }
    }
    // channel의 모든 client에 reply 전송
    *this << RPL_CHANNELJOIN(*client, _name);
    *client << RPL_NAMREPLY_353(client->getNickname(), _name, user_list);
    *client << RPL_ENDOFNAMES_366(client->getNickname(), _name);
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

bool Server::isValidChannel(const std::string &channel) {
    if (channel.length() < 2 || channel.size() > CHANNEL_LENGTH) {
        return false;
    }
    return (channel[0] == '#' || channel[0] == '&');
}

Channel *Server::getExistingChannel(const std::string &channel) {
    for (std::set<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->getName() == channel) {
            return *it;
        }
    }
    return NULL;
}