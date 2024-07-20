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