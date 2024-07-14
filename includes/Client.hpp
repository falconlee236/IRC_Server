#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>

class Client {
private:
    const int _client_fd;

public:
    Client(int);
    ~Client();
};

#endif