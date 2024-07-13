#include <sstream>
#include "../includes/Server.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "Invalid argument, need 2 arguments\n";
        std::cerr << "1st: Port number, 2nd: password\n";
        exit(1);
    }

    std::istringstream iss(av[1]);
    int port;
    iss >> std::noskipws >> port;
    if (!iss.eof() || iss.fail() || port <= 0 || port > 65535) {
        std::cerr << "Invalid port number\n";
        return 1;
    }

    try {
        Server server(port, av[2]);
        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}