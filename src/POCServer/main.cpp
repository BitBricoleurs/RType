//
// Created by Clément Lagasse on 06/10/2023.
//

#include "Server.hpp"
#include "GameEngine.hpp"
#include "NetworkClientConnection.hpp"
#include "NetworkClientRequestDisconnect.hpp"
#include "NetworkClientDisconnecting.hpp"
#include "NetworkStartServer.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"

int main(void) {
    GameEngine::GameEngine engine;

    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
    auto server = std::make_shared<Network::Server>(4444, 2, 2, queue);

    auto networkStart = std::make_shared<NetworkStartServer>(server);
    auto networkClientConnection = std::make_shared<NetworkClientConnection>(server);
    auto input = std::make_shared<NetworkInput>(queue);
    auto output = std::make_shared<NetworkOutput>(server);

    engine.addEvent("NETWORK_START_SERVER", networkStart);
    engine.addEvent("NETWORK_CLIENT_CONNECTION", networkClientConnection);
    engine.addSystem("NETWORK_INPUT", input, 0);
    engine.addEvent("SEND_NETWORK", output);

    engine.queueEvent("NETWORK_START_SERVER", std::make_any<size_t>(0));
    engine.run();
    return 0;
}