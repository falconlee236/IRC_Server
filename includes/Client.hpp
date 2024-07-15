#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <unistd.h>

class Client {
private:
    const int _socket;
    std::string _nickname;

public:
    Client(int);
    ~Client();

    int getSocket() const;
    const std::string& getNickname() const;

    void setNickname(const std::string&);
};

#endif