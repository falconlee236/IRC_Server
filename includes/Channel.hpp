#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include "Client.hpp"
#include <bitset>
#include <set>
#include <map>

//TODO - MODE는 i, t, k, l, o 구현 필요
/*
//SECTION - mode 파라미터 설명
i: channel을 invite only로 만든다 (INVITE command 참고)
l: 최대 channel 수를 설정한다.
t: topic을 설정 가능/불가능 하게 만든다 (TOPIC command 참고)
k: channel에 key (password)를 설정한다 (default는 none)
o: channel operator(관리자)권한을 주거나(give) 뺏는다(take).
//!SECTION
*/
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
	enum _ChannelFlag{
		INVITE_ONLY, //LINK - i mode flag
		SET_USER_LIMIT, //LINK - l mode flag
		SET_TOPIC, //LINK - t mode flag
		SET_KEY //LINK - k mode flag
	};
	std::bitset<4> _flags;
	std::set<Client *> _clients;
	std::set<Client *> _operators;

	//SECTION - l mode flag variables
	// std::size_t _max_clients;
	//!SECTION

	//SECTION - i mode flag variables
	std::set<Client *> _guests;
	//!SECTION

	//SECTION - t mode flag variables
	//NOTE - Topic set by sang [root@127.0.0.1] [Thu Jul 18 16:25:46 2024]
	std::string _topic;
	// Client *_topic_setter;
	// std::time_t _topic_set_time;
	//!SECTION

	//SECTION - k mode flag variables
	std::string _key; //NOTE - Channel password
	//!SECTION

public:
	Channel(std::string);
	~Channel();

public:
	Channel(void);
	Channel(const Channel &obj);
	Channel& operator=(const Channel &obj);
};

#endif