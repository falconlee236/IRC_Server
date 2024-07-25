#ifndef NUMERICREPLY_HPP
#define NUMERICREPLY_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
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

inline std::string to_string(int number) {
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

inline std::string normal_reply_helper(int number, const std::string& target, const std::string& message) {
    std::ostringstream ss;
    ss << std::setw(3) << std::setfill('0') << number;
    return ss.str() + " " + target + " " + message + CRLF;
}

#define ERROR_REPLY(number, target, message) \
    (to_string(number) + " " + target + " " + message + CRLF)
#define NORMAL_REPLY(number, target, message) \
     (normal_reply_helper(number, target, message))

// NOTE - PING_REPLIES
#define RPL_PONG(params) ("PONG :" + params + CRLF)

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

#define RPL_BRDCAST_MODE(client, channel, mode, params) (":" + USER_PREFIX(client) + " MODE " + (channel).getName() + " " + mode + " " + params + CRLF)

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
#define ERR_USERNOTINCHANNEL_441(target, user, channel_name) ERROR_REPLY(441, target, user + " " + channel_name + " :They aren't on that channel")
#define ERR_NOTONCHANNEL_442(target, channel_name) ERROR_REPLY(442, target, channel_name + " :You're not on that channel")

#define RPL_CHANNELPART(client, channel_name) (":" + USER_PREFIX(client) + " PART " + channel_name + CRLF)

// NOTE - TOPIC
#define RPL_NOTOPIC_331(target, channel_name) NORMAL_REPLY(331, target, channel_name + " :No topic is set")
#define RPL_TOPIC_332(target, channel_name, topic) NORMAL_REPLY(332, target, channel_name + " :" + topic)
#define ERR_CHANOPRIVSNEEDED_482(target, channel_name) ERROR_REPLY(482, target, channel_name + " :You're not channel operator")

#define RPL_CHANNELTOPIC(client, channel_name, topic) (":" + USER_PREFIX(client) + " TOPIC " + channel_name + " " + topic + CRLF)
#define RPL_CHANNELKICK(client, channel_name, user, message) (":" + USER_PREFIX(client) + " KICK " + channel_name + " " + user + " " + message + CRLF)

// NOTE - INVITE_REPLIES
#define ERR_NOSUCHNICK_401(target, invalid_nick) ERROR_REPLY(401, target, invalid_nick + " :No such nick/channel")

#define RPL_INVITING_341(client_name, target_name, channel_name) (":" + client_name + " INVITE " + target_name + " " + channel_name + CRLF)

#define RPL_PRIVMSG(client, target_name, message) (":" + USER_PREFIX(client) + " PRIVMSG " + target_name + " " + message + CRLF)

#endif