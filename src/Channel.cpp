#include "../includes/Channel.hpp"

Channel::Channel(std::string name) : _name(name){}

Channel::~Channel(){}

bool Channel::checkChannelOperator(Client *client){
	//STUB - Always true
	return true;
	return _operators.find(client) != _operators.end() ? true : false;
}

bool Channel::setChannelFlag(const std::vector<std::string> &params){
	std::string flags_str = params[1];
	// NOTE - +t-o+lk test 30 11
	try{
		for(size_t i = 0, cnt = 2; i < flags_str.length(); i++){
			if (flags_str[i] == '+'){
				i++;
				while (i < flags_str.length()){
					switch (flags_str[i]){
						case 'l':
							setFlag(_FlagOp::ADD, _ChannelFlag::SET_USER_LIMIT, params, cnt);
							break;
						case 'i':
							setFlag(_FlagOp::ADD, _ChannelFlag::INVITE_ONLY, params, cnt);
							break;
						case 't':
							setFlag(_FlagOp::ADD, _ChannelFlag::SET_TOPIC, params, cnt);
							cnt--;
							break;
						case 'k':
							setFlag(_FlagOp::ADD, _ChannelFlag::SET_KEY, params, cnt);
							break;
						case 'o':
							setOperator(_FlagOp::ADD, params, cnt);
							break;
						default:
							return false;
					}
					cnt++;
					i++;
				}
			} else if (flags_str[i] == '-'){
				i++;
				while (i < flags_str.length()){
					switch (flags_str[i]){
					case 'l':
						setFlag(_FlagOp::REMOVE, _ChannelFlag::SET_USER_LIMIT, params, cnt);
						break;
					case 'i':
						setFlag(_FlagOp::REMOVE, _ChannelFlag::INVITE_ONLY, params, cnt);
						break;
					case 't':
						setFlag(_FlagOp::REMOVE, _ChannelFlag::SET_TOPIC, params, cnt);
						cnt--;
						break;
					case 'k':
						setFlag(_FlagOp::REMOVE, _ChannelFlag::SET_KEY, params, cnt);
						break;
					case 'o':
						setOperator(_FlagOp::REMOVE, params, cnt);
						break;
					default:
						return false;
					}
					cnt++;
					i++;
				}
			}
		}
	} catch (std::exception &e){
		return false;
	}
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