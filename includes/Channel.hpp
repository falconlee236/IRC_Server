#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include "Client.hpp"

class Channel{
private:
/*
//NOTE - Channel Name 규칙
1. &, # 으로만 시작하는 최대 200자 길이의 문자열
2. 채널 이름에는 ' '(공백), ^G(ASCII 7번), ','(쉼표)를 포함할 수 없음
3. 나머지는 모두 가능
4. 이름은 변경할 수 없음
*/
	const std::string _name;
public:
	Channel(std::string);
	~Channel();

public:
	Channel(void);
	Channel(const Channel &obj);
	Channel& operator=(const Channel &obj);
};

#endif