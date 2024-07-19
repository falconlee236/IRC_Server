#include "../../includes/Server.hpp"

/*STUB - mode test
user Input ->  Irssi Input ->  inspircd Output
/mode #hello +t -o test +l 30 +k 11 -> MODE #hello +t-o+lk test 30 11 -> sang!root@127.0.0.1 MODE #hello +lk 30 :11
/mode +t -t -> MODE #hello +t-t -> sang!root@127.0.0.1 MODE #hello :-t (맨 마지막만 설정)
/mode +o yoon -> MODE #hello +o yoon -> sang!root@127.0.0.1 MODE #hello +o :yoon
/mode -o yoon -> MODE #hello -o yoon -> sang!root@127.0.0.1 MODE #hello -o :yoon
/mode +o yoon -o yoon -> MODE #hello +o-o yoon yoon -> sang!root@127.0.0.1 MODE #hello +o-o yoon :yoon
/mode -o yoon +o yoon -> MODE #hello -o+o yoon yoon -> sang!root@127.0.0.1 MODE #hello +o :yoon
/mode -t +t -> MODE #hello -t+t -> sang!root@127.0.0.1 MODE #hello :+t

i, l, t, k, o
i, t는 매개변수가 없음
l (count)
k (key)
o (nickname)
이 필요
*/

void Server::mode(Client *client, const std::vector<std::string> params){
    if (!client->isRegistered){
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
    if (params.size() < 3){
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }
}