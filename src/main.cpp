#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_ntoa

int main(void){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);

    int binded = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (binded != 0) {
        std::cerr << "bind error!" << "\n";
        exit(1);
    }

    binded = listen(server_socket, 5);
    if (binded != 0) {
        std::cerr << "bind error!" << "\n";
        exit(1);
    }
    
    while(1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

        while(1){
            char buffer[1024] = { 0, };
            recv(client_socket, buffer, sizeof(buffer), 0);
            std::cout << "received! : " << buffer << "\n";
            
            std::string msg = buffer;
            msg = "send: " + msg;
            send(client_socket, msg.c_str(), msg.size(), 0);
        }
    }
    return 0;
}