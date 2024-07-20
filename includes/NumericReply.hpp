#ifndef NUMERICREPLY_HPP
#define NUMERICREPLY_HPP

#include <iostream>
#include <sstream>
#include <iomanip>

#define CLIENT_SOURCE(client) ((client).getNickname() + "!" + (client).getUsername() + "@" + (client).getHostname())

#define ERROR_REPLY(number, target, message) \
    (std::to_string(number) + " " + target + " " + message + "\r\n")
#define NORMAL_REPLY(number, target, message) \
    ((std::stringstream() << std::setw(3) << std::setfill('0') << number).str() + " " + target + " " + message + "\r\n")

// NOTE - REGISTER
#define RPL_WELCOME_001(client) \
    NORMAL_REPLY(001, (client).getNickname(), ":Welcome to the Internet Relay Network " + CLIENT_SOURCE((client)))
#define RPL_YOURHOST_002(client) \
    NORMAL_REPLY(002, (client).getNickname(), ":Your host is " + (client).getServername() + " running version ircserv1.0")
#define RPL_CREATED_003(client, date) \
    NORMAL_REPLY(003, (client).getNickname(), ":This server was created " + date)

// NOTE - PASS_REPLIES
#define ERR_ALREADYREGISTRED_462(target) ERROR_REPLY(462, target, ":You may not reregister")
#define ERR_PASSWDMISMATCH_464(target) ERROR_REPLY(464, target, ":Password incorrect")

//NOTE - NICK_REPLIES
#define ERR_UNKNOWNCOMMAND_421(target, command) ERROR_REPLY(421, target, command + " :Unknown command")
#define ERR_NONICKNAMEGIVEN_431(target) ERROR_REPLY(431, target, ":No nickname given")
#define ERR_ERRONEUSNICKNAME_432(target, invalidNick) ERROR_REPLY(432, target, invalidNick + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE_433(target, invalidNick) ERROR_REPLY(433, target, invalidNick + " :Nickname is already in use")
#define ERR_NOTREGISTERED_451(target) ERROR_REPLY(451, target, ":You have not registered")

#define RPL_NICKNAMECHANGE(target, oldNick) (":" + oldNick + " NICK " + target + "\r\n")

//NOTE - MODE_REPLIES
#define ERR_BADCHANMASK_476(target, channel) ERROR_REPLY(476, target, (channel) + " :Bad Channel Mask")
#define ERR_UMODEUNKNOWNFLAG_501(target) ERROR_REPLY(501, target, ":Unknown mode flag")

#define RPL_BRDCAST_MODE(client, channel, mode, params) (":" + CLIENT_SOURCE((client)) + " MODE " + (channel).getChannelName() + " " + (mode) + " " + (params) + "\r\n")

//NOTE - ERR_REPLIES
#define ERR_NEEDMOREPARAMS_461(target) ERROR_REPLY(461, target, ":Not enough parameters")
#endif