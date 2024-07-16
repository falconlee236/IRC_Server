#ifndef NUMERICREPLY_HPP
#define NUMERICREPLY_HPP

#include <iostream>

#define ERROR_REPLY(number, target, message) \
    (std::to_string(number) + " " + target + " " + message + "\r\n")
#define NORMAL_REPLY(number, target, message) \
    (std::to_string(number) + " " + target + " " + message + "\r\n")

#define ERR_NONICKNAMEGIVEN_431(target) ERROR_REPLY(431, target, ":No nickname given")
#define ERR_ERRONEUSNICKNAME_432(target, invalidNick) ERROR_REPLY(432, target, invalidNick + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE_433(target, invalidNick) ERROR_REPLY(433, target, invalidNick + " :Nickname is already in use")
#define ERR_NOTREGISTERED_451(target) ERROR_REPLY(451, target, ":You have not registered")

#define RPL_NICKNAMECHANGE(target, oldNick) (":" + oldNick + " NICK " + target)

#endif