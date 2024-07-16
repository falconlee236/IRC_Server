#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <unistd.h>

class Client {
private:
    const int _socket;
    std::string _nickname;
    std::string _username;
    std::string _hostname;
    std::string _servername;
    std::string _realname;
    bool _isRegistered;

public:
    Client(int);
    ~Client();

    int getSocket() const;
    const std::string& getNickname() const;

    void setNickname(const std::string &);
    void setUserInfo(const std::string &, const std::string &, const std::string &, const std::string &);

    bool isRegistered() const;
};

#endif