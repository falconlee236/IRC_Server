#include "../includes/Client.hpp"

Client::Client(void) 
    : _client_fd(-1), _client_port(-1), _client_ip("") {}

Client::Client(int client_fd, int client_port, std::string client_ip) 
    : _client_fd(client_fd), _client_port(client_port), _client_ip(client_ip) {
    (void) _client_fd;
    (void) _client_port;
    (void) _client_ip;
}

Client::~Client() {
    close(_client_fd);
}