#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"

// NOTE - INVITE <nickname><channel> 
void Server::invite(Client *client, const std::vector<std::string> params){
    if (!client->isRegistered){
        *client << ERR_NOTREGISTERED_451(client->getNickname());
        return;
    }
    if (params.size() < 2){
        *client << ERR_NEEDMOREPARAMS_461(client->getNickname());
        return;
    }
    // NOTE - 내가 명령어를 사용할 때 아무 체널에 있어야함 - Mode에도 넣어야함
    Channel *myChannel = getExistingChannel(client->getNickname());
    if (!myChannel){
        *client << ERR_NOTONCHANNEL_442(client->getNickname(), params[1]);
        return;
    }
    //  NOTE - 이미 있는 이름인 경우가 아니면 존재하지 않는 사용자
    Client *targetClient = getClientbyNickname(params[0]);
    if (!targetClient){
        *client << ERR_ERR_NOSUCHNICK_401(params[0]);
        return;
    }
    //NOTE - 대상 채널이 없을 때
    Channel *targetChannel = getExistingChannel(params[1]);
    if (!targetChannel){
        *client << ERR_NOSUCHCHANNEL_403(client->getNickname(), params[1]);
        return;
    }
    //TODO - MODE +i 채널에 사용자를 초대하기 위해서는 초대를 보내는 client가 해달 채널의 운영자여야한다.
    targetChannel->addGuest(targetClient);
    *targetChannel << RPL_INVITING_341(client->getNickname(), targetClient->getNickname(), targetChannel->getName());
    *client << RPL_INVITING_341(client->getNickname(), targetClient->getNickname(), targetChannel->getName());
}