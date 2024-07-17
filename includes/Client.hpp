#ifndef CLIENT_HPP
#define CLIENT_HPP
#define BUFFER_SIZE 1024
#define SOCKET_LINE_SIZE 512
#define CRLF "\r\n"

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <iostream>

class Client {
private:
    const int _client_fd;
    const int _client_port;
    const std::string _client_ip;
    std::string _read_data;
    std::string _write_data;

    std::string _nickname;
    std::string _username;
    std::string _hostname;
    std::string _servername;
    std::string _realname;

public:
    bool isPassConfirmed;
    bool isNicknameSet;
    bool isUserInfoSet;

    Client(void);
    Client(int client_fd, int client_port, std::string client_ip);
    ~Client();
    Client(const Client& obj);
    Client& operator= (const Client& obj);

    int getSocket() const;
    const std::string& getNickname() const;

    void setNickname(const std::string &);
    void setUserInfo(const std::string &, const std::string &, const std::string &, const std::string &);

    bool isRegistered() const;

    Client &operator<<(const std::string &data);
    Client &operator>>(std::string &data);

    Client &operator<<(const int socket_fd);
    Client &operator>>(const int socket_fd);
    
    class ClientDisconnectException : public std::exception{
    public:
        const char *what(void) const throw();
    };

    class CannotFoundCRLFException : public std::exception{
    public:
        const char *what(void) const throw();
    };

    class LineTooLongException : public std::exception{
    public:
        const char *what(void) const throw();
    };
};

#endif