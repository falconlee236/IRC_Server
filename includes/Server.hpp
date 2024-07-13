#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Server {
private:
    // member variables
    const int _port;
    const std::string _password;
    const int _server_fd;
    struct sockaddr_in _server_addr;
    const int _kqueue_fd;

    void initServerInfo();
    void connectNewClient();
    void handleClientEvent(struct kevent &);
    void removeClient(int);

public:
    Server(int, std::string);
    ~Server();

    void run();
};

#endif