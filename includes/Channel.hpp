#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include "Client.hpp"
#include <bitset>
#include <set>
#include <map>
#include <sstream>

#define CHANNEL_LENGTH 200

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
    std::map<std::string, Client *> _clients_map;
    std::set<Client *> _operators;
    std::map<std::string, Client *> _operators_map;
    enum _FlagOp{
        ADD,
        REMOVE
    };

    //SECTION - l mode flag variables
    std::size_t _max_clients;
    //!SECTION

    //SECTION - i mode flag variables
    std::set<Client *> _guests;
    std::map<std::string, Client *> _guests_map;
    //!SECTION

    //TODO - topic setter, set time 사용하기
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

    const std::string& getName() const;

    void addClient(Client *);
    void addOperator(Client *);
    void removeClient(Client *);

    bool isClientInChannel(Client *);
    bool isModeSet(_ChannelFlag);

    void join(Client *, const std::string &);
    void part(Client *);

    Channel &operator<<(const std::string &);

    bool isClientInOperator(Client *);
    bool setChannelFlag(const std::vector<std::string> &);
    size_t getClientNumber(void);
    void printChannelInfo(void);

private:
    void setFlag(enum _FlagOp, enum _ChannelFlag, const std::vector<std::string> &, int);
    void setOperator(enum _FlagOp, const std::vector<std::string> &, int);

public:
    Channel(void);
    Channel(const Channel &obj);
    Channel& operator=(const Channel &obj);
};

#endif