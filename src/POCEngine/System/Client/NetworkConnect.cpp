//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkConnect.hpp"

NetworkInitConnection::NetworkInitConnection(std::shared_ptr<Network::Client> &client) : _client(client)
{
}

void NetworkInitConnection::update(GameEngine::ComponentsContainer &componentsContainer,
                                   GameEngine::EventHandler &eventHandler)
{
    if (_client->isConnected())
        return;
    Network::Endpoint endpoint = {};
    try {
        endpoint = std::any_cast<Network::Endpoint>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
    }
    _client->connect(endpoint.ip, endpoint.port);
}
