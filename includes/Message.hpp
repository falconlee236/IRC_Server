#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

class Message {
private:
	std::queue<std::string> msg_queue;
	std::vector<std::string> splitN(const std::string& str, char delimiter, size_t n);

public:
	Message(void);
	Message(std::string str);
	~Message();
	Message(const Message& obj);
	Message& operator= (const Message& obj);

	void getClientMsg(std::string str);
};

#endif
