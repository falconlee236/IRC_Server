#ifndef NUMERICREPLY_HPP
#define NUMERICREPLY_HPP

#include <iostream>
#include <sstream>
#include <iomanip>

// <message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
// <prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
// <command>  ::= <letter> { <letter> } | <number> <number> <number>
// <SPACE>    ::= ' ' { ' ' }
// <params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
// <middle>   ::= <Any *non-empty* sequence of octets not including SPACE or NUL or CR or LF, the first of which may not be ':'>
// <trailing> ::= <Any, possibly *empty*, sequence of octets not including NUL or CR or LF>
// <crlf>     ::= CR LF

#define CRLF "\r\n"
#define USER_PREFIX(client) ((client).getNickname() + "!" + (client).getUsername() + "@" + (client).getHostname())

#define ERROR_REPLY(number, target, message) \
    (std::to_string(number) + " " + target + " " + message + CRLF)
#define NORMAL_REPLY(number, target, message) \
    ((std::stringstream() << std::setw(3) << std::setfill('0') << number).str() + " " + target + " " + message + CRLF)

// NOTE - REGISTER
#define RPL_WELCOME_001(client) \
    NORMAL_REPLY(001, (client).getNickname(), ":Welcome to the Internet Relay Network " + USER_PREFIX(client))
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

#define RPL_NICKNAMECHANGE(target, oldNick) (":" + oldNick + " NICK " + target + CRLF)

//NOTE - MODE_REPLIES
#define ERR_UMODEUNKNOWNFLAG_501(target) ERROR_REPLY(501, target, ":Unknown mode flag")
#define ERR_CHANOPRIVSNEEDED_482(target, channel_name) ERROR_REPLY(482, target, channel_name + " :You're not channel operator")

#define RPL_BRDCAST_MODE(client, channel, mode, params) (":" + USER_PREFIX((client)) + " MODE " + (channel).getName() + " " + (mode) + " " + (params) + "\r\n")

    // NOTE - ERR_REPLIES
#define ERR_NEEDMOREPARAMS_461(target) ERROR_REPLY(461, target, ":Not enough parameters")

    // NOTE - JOIN_REPLIES
#define ERR_USERONCHANNEL_443(target, channel_name) ERROR_REPLY(443, target, target + " " + channel_name + " :is already on channel")
#define ERR_CHANNELISFULL_471(target, channel_name) ERROR_REPLY(471, target, channel_name + " :Cannot join channel (+l)")
#define ERR_INVITEONLYCHAN_473(target, channel_name) ERROR_REPLY(473, target, channel_name + " :Cannot join channel (+i)")
#define ERR_BADCHANNELKEY_475(target, channel_name) ERROR_REPLY(475, target, channel_name + " :Cannot join channel (+k)")
#define ERR_BADCHANMASK_476(target, channel_name) ERROR_REPLY(476, target, channel_name + " :Bad Channel Mask")

#define RPL_CHANNELJOIN(client, channel_name) (":" + USER_PREFIX(client) + " JOIN " + channel_name + CRLF)
#define RPL_NAMREPLY_353(target, channel_name, name_list) NORMAL_REPLY(353, target, "= " + channel_name + " :" + name_list)
#define RPL_ENDOFNAMES_366(target, channel_name) NORMAL_REPLY(366, target, channel_name + " :End of /NAMES list")

#define ERR_NOSUCHCHANNEL_403(target, channel_name) ERROR_REPLY(403, target, channel_name + " :No such channel")
#define ERR_NOTONCHANNEL_442(target, channel_name) ERROR_REPLY(442, target, channel_name + " :You're not on that channel")

#define RPL_CHANNELPART(client, channel_name) (":" + USER_PREFIX((client)) + " PART " + channel_name + CRLF)

#endif