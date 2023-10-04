#include <iostream>
#include <memory>
#include <any>
#include "NetworkLib/Client.hpp"
#include "NetworkLib/Message.hpp"

int main() {
    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> forwardQueue;
    Network::Client client(1, forwardQueue);
    client.connect("127.0.0.1", 4444);
    std::cout << "Hello, World!" << std::endl;
    std::string str = "Hello";
    std::vector< std::any> data = {std::any(str)};
    std::vector<unsigned int> ids = {1, 2, 3};
    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("HELLO", ids, "STRING", data);
    client.send(message);
    while (1);
    return 0;
}
