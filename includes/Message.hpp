#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Message {
public:
    typedef enum CMD {
        NONE,  // 0
        CAP,
        PASS,
        NICK,
        USER,
        QUIT,
        JOIN,
        PART,
        TOPIC,
        MODE,
        INVITE,
        KICK,
        PRIVMSG,
        PING,
        BOT,
        CMD_SIZE
    } e_cmd;

private:
    static const std::string _commandList[CMD_SIZE + 1];
    e_cmd _cmd_type;
    std::string _cmd;
    std::vector<std::string> _params;

    e_cmd findCommand(const std::string &cmd);
    std::vector<std::string> splitMessage(const std::string &str);

public:
    Message();
    Message(std::string str);
    ~Message();
    Message(const Message& obj);
    Message& operator= (const Message& obj);

    e_cmd getCmdType();
    const std::string getCmd();
    const std::vector<std::string> getParams();

    static std::vector<std::string> split(const std::string &str, char delimiter);
};

#endif