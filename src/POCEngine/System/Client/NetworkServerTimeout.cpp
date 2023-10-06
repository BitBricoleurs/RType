//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkServerTimeout.hpp"

NetworkServerTimeout::NetworkServerTimeout(std::shared_ptr<Network::Client> &client) : _client(client)
{
}

void NetworkServerTimeout::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    size_t entityId = 0;
    try {
        entityId = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
        }
    if (entityId == 0)
        return;
    componentsContainer.deleteEntity(entityId);
    _client->disconnect();
    // TODO : Send To ECS that the client is disconnected
}