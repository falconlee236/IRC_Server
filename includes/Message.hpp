#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <iostream>
#include <string>
#include <queue>

class Message {
private:
	std::queue<std::string> msg_queue;

public:
	Message(void);
	Message(std::string str);
	~Message();
	Message(const Message& obj);
	Message& operator= (const Message& obj);

	void get_client_msg(std::string str);
};

#endif
