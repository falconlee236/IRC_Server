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
		for(size_t i = 0, idx = 2; i < flags_str.length(); i++){
			if (flags_str[i] == '+'){
				i++;
				while (i < flags_str.length()){
					switch (flags_str[i]){
						case 'l':
							setFlag(Channel::ADD, Channel::SET_USER_LIMIT, params, idx);
							break;
						case 'i':
							setFlag(Channel::ADD, Channel::INVITE_ONLY, params, idx);
							break;
						case 't':
							setFlag(Channel::ADD, Channel::SET_TOPIC, params, idx);
							idx--;
							break;
						case 'k':
							setFlag(Channel::ADD, Channel::SET_KEY, params, idx);
							break;
						case 'o':
							setOperator(Channel::ADD, params, idx);
							break;
						default:
							return false;
					}
					idx++;
					i++;
				}
			} else if (flags_str[i] == '-'){
				i++;
				while (i < flags_str.length()){
					switch (flags_str[i]){
					case 'l':
						setFlag(Channel::REMOVE, Channel::SET_USER_LIMIT, params, idx);
						break;
					case 'i':
						setFlag(Channel::REMOVE, Channel::INVITE_ONLY, params, idx);
						break;
					case 't':
						setFlag(Channel::REMOVE, Channel::SET_TOPIC, params, idx);
						idx--;
						break;
					case 'k':
						setFlag(Channel::REMOVE, Channel::SET_KEY, params, idx);
						break;
					case 'o':
						setOperator(Channel::REMOVE, params, idx);
						break;
					default:
						return false;
					}
					idx++;
					i++;
				}
			}
		}
	} catch (std::exception &e){
		return false;
	}
	return true;
}

void Channel::setOperator(enum _FlagOp flag_op, const std::vector<std::string> &params , int param_idx){
	if (param_idx >= params.size() || _clients_map.find(params[param_idx]) == _clients_map.end())
		throw std::runtime_error("Invalid parameters");
	
	std::string op_client_name = params[param_idx];
	Client *op_client = _clients_map[op_client_name];
	if (flag_op == Channel::ADD){
		_operators.insert(op_client);
		_operators_map[op_client_name] = op_client;
	} else {
		_operators.erase(op_client);
		_operators_map.erase(op_client_name);
	}
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