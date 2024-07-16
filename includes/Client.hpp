#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>
#include <string>
#include <iostream>

class Client {
private:
    const int _client_fd;
    const int _client_port;
    const std::string _client_ip;

public:
    Client(void);
    Client(int client_fd, int client_port, std::string client_ip);
    ~Client();
};

#endif