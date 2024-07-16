#include "../includes/Server.hpp"

Server::Server(int port, std::string password)
    : _port(port),
      _password(password),
      _server_fd(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)),
      _kqueue_fd(kqueue()) {
    // 소켓 (IPv4, TCP)
    if (_server_fd < 0) {
        throw std::runtime_error("Socket creation failed");
    }
    if (_kqueue_fd < 0) {
        throw std::runtime_error("Kqueue creation failed");
    }

    initServerInfo();
    // client의 요청을 기다리기 시작
    if (listen(_server_fd, 5) < 0) {
        throw std::runtime_error("Listen failed");
    }
    std::cout << "IRC server is running on port: " << _port << "\n";
}

Server::~Server() {
    close(_server_fd);
    close(_kqueue_fd);

    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        delete it->second;
    }
}

void Server::initServerInfo() {
    // SOL_SOCKET의 SO_REUSEADDR은 커널에서 이미 바인딩한 주소를 재사용 하게 해줌 (에러 방지)
    int opt = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error("Setsockopt failed");
    }

    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin_family = AF_INET;                   // 주소체계: ipv4
    _server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    // INADDR_ANY 자신의 모든 랜카드로 ip를 받을 수 있음
    _server_addr.sin_port = htons(_port);                // Server ip의 PORT번호 지정

    // socket과 ip를 연결하는 작업
    if (bind(_server_fd, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) < 0) {
        throw std::runtime_error("Bind failed");
    }
}

void Server::run() {
    // kqueue에 server_socket 등록
    // EVFILT_READ: 읽기 이벤트
    // EV_ADD: 이벤트 등록
    // EV_ENABLE: 이벤트 활성화
    struct kevent change_event;
    EV_SET(&change_event, _server_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if (kevent(_kqueue_fd, &change_event, 1, NULL, 0, NULL) < 0) {
        throw std::runtime_error("Kevent registration failed");
    }

    while (true) {
        // 발생한 event가 반환될 배열
        struct kevent events[10];
        int new_events = kevent(_kqueue_fd, NULL, 0, events, 10, NULL);
        if (new_events < 0) {
            throw std::runtime_error("Kevent failed");
        }

        for (int i = 0; i < new_events; ++i) {
            if ((int)events[i].ident == _server_fd) {
                connectNewClient();
            } else if (events[i].filter == EVFILT_READ) {
                handleClientEvent(events[i]);
            }
        }
    }
}

void Server::connectNewClient() {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(_server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0) {
        std::cerr << "Failed to accept new connection\n";
        return;
    }

    std::string client_ip = std::string(inet_ntoa(client_addr.sin_addr));
    int client_port = ntohs(client_addr.sin_port);
    std::cout << "Client " << client_ip << ":" << client_port << " connected\n";

    Client *new_client = new Client(client_socket, client_port, client_ip);
    _clients[client_socket] = new_client;

    struct kevent change_event;
    EV_SET(&change_event, client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if (kevent(_kqueue_fd, &change_event, 1, NULL, 0, NULL) < 0) {
        std::cerr << "Failed to register client socket with kqueue\n";
        removeClient(client_socket);
    }
}

void Server::handleClientEvent(struct kevent &event) {
    int client_socket = event.ident;
    char buffer[1024] = {0};
    ssize_t recv_byte = recv(client_socket, buffer, sizeof(buffer), 0);
    if (recv_byte <= 0) {
        std::cout << "Client disconnected\n";
        removeClient(client_socket);
        return;
    }

    std::cout << "Received: " << buffer << "\n";
    std::string msg = "send: " + std::string(buffer);
    send(client_socket, msg.c_str(), msg.size(), 0);
}

void Server::removeClient(int client_socket) {
    struct kevent change_event;
    EV_SET(&change_event, client_socket, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    kevent(_kqueue_fd, &change_event, 1, NULL, 0, NULL);

    std::map<int, Client*>::iterator it = _clients.find(client_socket);
    if (it != _clients.end()) {
        delete it->second;
        _clients.erase(client_socket);
    }
}