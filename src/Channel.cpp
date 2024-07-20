#include "../includes/Channel.hpp"

Channel::Channel(std::string name) : _name(name){}

Channel::~Channel(){}


Channel::Channel(void) : _name(""){
    throw std::runtime_error("Channel(): consturctor is not allowed");
}
Channel::Channel(const Channel &obj) : _name(obj._name){
    throw std::runtime_error("Channel(): copy consturctor is not allowed");
}

Channel& Channel::operator=(const Channel &obj){
    (void) obj;
    throw std::runtime_error("Channel(): operator= is not allowed");
    return *this;
}

std::string Channel::getName() const {
    return _name;
}

void Channel::addClient(Client *client) {
    _clients.insert(client);
    _clients_map[client->getNickname()] = client;
}

void Channel::addOperator(Client *client) {
    _operators.insert(client);
    _operators_map[client->getNickname()] = client;
}

void Channel::removeClient(Client *client) {
    _clients.erase(client);
    _clients_map.erase(client->getNickname());
    _operators.erase(client);
    _operators_map.erase(client->getNickname());
    _guests.erase(client);
    _guests_map.erase(client->getNickname());
}

bool Channel::isClientInChannel(Client *client) {
    return _clients.find(client) != _clients.end();
}

bool Channel::isModeSet(_ChannelFlag flag) {
    return _flags.test(flag);
}

Channel &Channel::operator<<(const std::string &message) {
    for (std::set<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        **it << message;
        **it >> (*it)->getSocket();
    }
    return *this;
}