//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkReceiveDisconnectApply.hpp"

NetworkRecieveDisconnectApply::NetworkRecieveDisconnectApply(std::shared_ptr<Network::Client> &client) : _client(client)
{
}

void NetworkRecieveDisconnectApply::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    _client->disconnect();
}
