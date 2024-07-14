#include "../includes/Client.hpp"

Client::Client(int fd) : _client_fd(fd) {
    (void) _client_fd;
}

Client::~Client() {
    close(_client_fd);
}