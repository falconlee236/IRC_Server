#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"

void Server::topic(Client *client, const std::vector<std::string> params) {
    if (!client->isRegistered) {
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
    if (params.empty()) {
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }

    Channel *channel = getExistingChannel(params[0]);
    if (channel) {
        std::string topic_message = std::string();
        for (std::vector<std::string>::const_iterator it = params.begin() + 1; it != params.end(); ++it) {
            topic_message += *it + " ";
        }
        channel->topic(client, topic_message);
    } else {
        *client << ERR_NOSUCHCHANNEL_403(client->getNickname(), params[0]);
    }
}

void Channel::topic(Client *client, const std::string &topic) {
    if (topic.empty()) {
        if (_topic.empty()) {
            *client << RPL_NOTOPIC_331(client->getNickname(), _name);
        } else {
            *client << RPL_TOPIC_332(client->getNickname(), _name, _topic);
        }
    } else {
        if ((isModeSet(SET_TOPIC) && !isOperator(client)) || !isModeSet(SET_TOPIC)) {
            *client << ERR_CHANOPRIVSNEEDED_482(client->getNickname(), _name);
        } else {
            setTopic(client, topic);
            *this << RPL_CHANNELTOPIC(*client, _name, topic);
        }
    }
}