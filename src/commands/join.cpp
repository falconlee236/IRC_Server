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
            _channels.insert(new Channel(*it));
            // TODO: _clients, _operators에 client 넣기
        }
    }
}

// TODO: 조건 수정
bool Server::isValidChannel(const std::string &channel) {
    return !channel.empty() && (channel[0] == '#' || channel[0] == '&');
}

Channel *Server::getExistingChannel(const std::string &channel) {
    for (std::set<Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->getName() == channel) {
            return *it;
        }
    }
    return NULL;
}