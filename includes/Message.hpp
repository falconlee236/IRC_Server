#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

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
		CMD_SIZE
	} e_cmd;

private:
	static const std::string _commandList[CMD_SIZE + 1];
	e_cmd _cmd_type;
	std::string _params;
	std::vector<std::string> splitN(const std::string& str, char delimiter, size_t n);
	e_cmd findCommand(const std::string cmd_str);

public:
	Message(void);
	Message(std::string str);
	~Message();
	Message(const Message& obj);
	Message& operator= (const Message& obj);

	e_cmd getCommand(void);
	const std::string getParams(void);
};

#endif
