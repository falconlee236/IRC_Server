#include "../includes/Channel.hpp"

Channel::Channel(std::string name) : _name(name){}

Channel::~Channel(){

}


Channel::Channel(void) : _name(""){
	throw std::runtime_error("Channel(): consturctor is not allowed");
}
Channel::Channel(const Channel &obj){
	throw std::runtime_error("Channel(): copy consturctor is not allowed");
}

Channel& Channel::operator=(const Channel &obj){
	throw std::runtime_error("Channel(): operator= is not allowed");
	return *this;
}