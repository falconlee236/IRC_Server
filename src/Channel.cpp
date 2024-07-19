#include "../includes/Channel.hpp"

Channel::Channel(std::string name) : _name(name){}

Channel::~Channel(){}

bool Channel::checkChannelOperator(Client *client){
	//STUB - Always true
	return true;
	return _operators.find(client) != _operators.end() ? true : false;
}

bool Channel::setChannelFlag(const std::string &flag_str){
	(void)flag_str;
	return true;
}

const std::string& Channel::getChannelName(void){
	return this->_name;
}


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