#include "../../includes/Server.hpp"

void Server::bot(Client *client, const std::vector<std::string> params){
    (void) params;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);
    std::string nickname_list[10] = {
        "Charlie", "Danny", "Emerson", "Lara", "Emma", 
        "Raven", "Margot", "Wanda", "Elizabeth", "Vivian"
    };
    *client << NORMAL_REPLY(256, client->getNickname(), "The bot generate nickname: \"" + nickname_list[dis(gen)] + "\"");
}