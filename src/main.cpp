#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_ntoa

int main(void){
    /*
    //SECTION
    domain - AF_INET = ipv4, 
    type - SOCK_STREAM = tcp,
    protocol - IPPROTO_TCP = TCP based socket
    //!SECTION
    */
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //NOTE - SOL_SOCKET의 SO_REUSEADDR은 커널에서 이미 바인딩한 주소를 재사용 하게 해줌. (에러 방지)
    bool opt = true;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //NOTE - IPV$ socket address인 경우 sockaddr_in, 그 상위는 sockaddr
    // 서버 주소 설정하는 과정.
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    // NOTE - 주소체계 : ipv4
    server_addr.sin_family = AF_INET;
    // NOTE - INADDR_ANY 자신의 모든 랜카드로 ip를 받을 수 있음.
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // NOTE - Server ip의 PORT번호 지정
    server_addr.sin_port = htons(8080);

    // NOTE - socket과 ip를 연경하는 작업
    int binded = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (binded != 0) {
        std::cerr << "bind error!" << "\n";
        exit(1);
    }

    // NOTE - client의 요청을 기다리기 시작
    binded = listen(server_socket, 5);
    if (binded != 0) {
        std::cerr << "bind error!" << "\n";
        exit(1);
    }
    
    while(1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            std::cerr << "get client socket error!" << "\n";
            exit(1);
        }

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