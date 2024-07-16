#include "../includes/Client.hpp"

Client::Client(void) 
    : _client_fd(-1), _client_port(-1), _client_ip("") {}

Client::Client(int client_fd, int client_port, std::string client_ip) 
    : _client_fd(client_fd),
      _client_port(client_port),
      _client_ip(client_ip),
      _nickname("nick") {
    (void) _client_fd;
    (void) _client_port;
    (void) _client_ip;
}

Client::~Client() {
    close(_client_fd);
}

int Client::getSocket() const {
    return _client_fd;
}

const std::string& Client::getNickname() const {
    return _nickname;
}
void Client::setNickname(const std::string& nickname) {
    _nickname = nickname;
}

// read from client socket
Client &Client::operator<<(const int socket_fd){
    char buffer[BUFFER_SIZE] = {0, };
    ssize_t recv_byte = recv(socket_fd, buffer, BUFFER_SIZE, 0);
    if (recv_byte <= 0)
        throw ClientDisconnectException();
    _read_data += std::string(buffer, recv_byte);
    return *this;
}
// write to client socket
Client &Client::operator>>(const int socket_fd){
    if (!_write_data.empty()){
        ssize_t send_byte = send(socket_fd, _write_data.c_str(), _write_data.size(), 0);
        if (send_byte <= 0)
            throw ClientDisconnectException();
        _write_data = _write_data.substr(send_byte);
    }
    return *this;
}

// data를 write data로 넣기
Client &Client::operator<<(const std::string &line) {
  _write_data += line;
  return *this;
}

// 읽은 것을 string으로 내보내기
Client &Client::operator>>(std::string &line) {
    std::string::size_type pos = _read_data.find(CRLF);
    if (pos == std::string::npos){
        line.clear();
        throw CannotFoundCRLFException();
    }
    if (pos + 2 > SOCKET_LINE_SIZE){
        _read_data = _read_data.substr(pos + 2);    
        throw LineTooLongException();
    }
    line = _read_data.substr(0, pos);
    _read_data = _read_data.substr(pos + 2);
    return *this;
}

const char* Client::ClientDisconnectException::what(void) const throw(){
    return "Client disconnected";
}

const char* Client::CannotFoundCRLFException::what(void) const throw(){
    return "Cannot found CRLF";
}

const char* Client::LineTooLongException::what(void) const throw(){
    return "Command Line is Too long";
}