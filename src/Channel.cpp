#include "../includes/Channel.hpp"

Channel::Channel(std::string name) : _name(name){
	_max_clients = 0;	
}

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
							idx--; //NOTE - i는 매개변수 없음
							break;
						case 't':
							setFlag(Channel::ADD, Channel::SET_TOPIC, params, idx);
							idx--; //NOTE - t는 매개변수 없음
							break;
						case 'k':
							setFlag(Channel::ADD, Channel::SET_KEY, params, idx);
							break;
						case 'o':
							setOperator(Channel::ADD, params, idx);
							break;
						case '-':
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
					case 'i': //NOTE - i는 매개변수 없음
						setFlag(Channel::REMOVE, Channel::INVITE_ONLY, params, idx);
                        idx--;
						break;
                    case 't': // NOTE - t는 매개변수 없음
                        setFlag(Channel::REMOVE, Channel::SET_TOPIC, params, idx);
						idx--;
						break;
					case 'k':
						setFlag(Channel::REMOVE, Channel::SET_KEY, params, idx);
						break;
					case 'o':
						setOperator(Channel::REMOVE, params, idx);
						break;
					case '+':
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
	if (param_idx >= static_cast<int>(params.size()) || _clients_map.find(params[param_idx]) == _clients_map.end())
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

void Channel::setFlag(enum _FlagOp flag_op, enum _ChannelFlag flag, const std::vector<std::string> &params,int param_idx){
	if (param_idx >= static_cast<int>(params.size()))
		throw std::runtime_error("Invalid parameters");
	std::string param = params[param_idx];
	std::istringstream iss(param);
	switch (flag){
		case Channel::SET_USER_LIMIT:
			int cnt;
			iss  >> std::noskipws >> cnt;
			if (iss.eof() && !iss.fail())
				throw std::runtime_error("invalid number");
			_flags[Channel::SET_USER_LIMIT] = (flag_op == Channel::ADD ? 1 : 0);
			_max_clients = cnt;
			break;
		case Channel::INVITE_ONLY:
			_flags[Channel::INVITE_ONLY] = (flag_op == Channel::ADD ? 1 : 0);
			break;
		case Channel::SET_TOPIC:
			_flags[Channel::SET_TOPIC] = (flag_op == Channel::ADD ? 1 : 0);
			break;
		case Channel::SET_KEY:
			_flags[Channel::SET_KEY] = (flag_op == Channel::ADD ? 1 : 0);
			_key = param;
			break;
	}
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

const std::string& Channel::getName() const {
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