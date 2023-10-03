#include <iostream>
#include "NetworkLib/Server.hpp"

int main() {
    Network::Server server(4444, 2, 1);
    server.start();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
