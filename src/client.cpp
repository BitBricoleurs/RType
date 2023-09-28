#include <iostream>
#include "NetworkLib/Client.hpp"

int main() {
    Network::Client client(10);
    client.connect("127.0.0.1", 4444);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
