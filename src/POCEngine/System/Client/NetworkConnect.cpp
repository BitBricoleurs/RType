//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkConnect.hpp"

NetworkConnect::NetworkConnect(std::shared_ptr<Network::Client> &client) : _client(client)
{
}

void NetworkConnect::update(GameEngine::ComponentsContainer &componentsContainer,
                                   GameEngine::EventHandler &eventHandler)
{
    if (_client->isConnected())
        return;
    Network::Endpoint endpoint("", 0);
    try {
        endpoint = std::any_cast<Network::Endpoint>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
    }
    _client->connect(endpoint.ip, endpoint.port);
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("CONNECT", ids, "", args);
    eventHandler.queueEvent("SEND_NETWORK", message);
}
