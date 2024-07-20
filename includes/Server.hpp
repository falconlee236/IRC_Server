#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <map>

#include "Client.hpp"
#include "Message.hpp"
#include "Channel.hpp"
#include "NumericReply.hpp"

class Server {
private:
    // member variables
    const int _port;
    const std::string _password;
    const int _server_fd;
    struct sockaddr_in _server_addr;
    const int _kqueue_fd;
    std::map<int, Client*> _clients;
    std::string _created_time;
    std::set<Channel *> _channels;

    void initServerInfo();
    void connectNewClient();
    void handleClientEvent(struct kevent &);
    void removeClient(int);
    void registerClient(Client *);

    bool isValidNickname(const std::string &);
    bool isDuplicateNickname(const std::string &);
    bool isValidChannel(const std::string &);
    Channel *getExistingChannel(const std::string &);
    void createChannel(const std::string &, Client *);

    void nick(Client *, const std::vector<std::string>);
    void pass(Client *, const std::vector<std::string>);
    void quit(Client *, const std::vector<std::string>);
    void user(Client *, const std::vector<std::string>);
    void join(Client *, const std::vector<std::string>);

public:
    Server(void);
    Server(int, std::string);
    ~Server();
    Server(const Server &obj);
    Server& operator=(const Server &obj);

    void run();
};

#endif