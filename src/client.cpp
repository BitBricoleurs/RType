#include <iostream>
#include "NetworkLib/Client.hpp"

int main() {
    Network::Client client(1);
    client.connect("127.0.0.1", 4444);
    std::cout << "Hello, World!" << std::endl;
    client.send("HELLO", {1, 2, 3}, "STRING", std::string("Hello"));
    while (1);
    return 0;
}
