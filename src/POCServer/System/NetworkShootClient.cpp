//
// Created by Clément Lagasse on 13/10/2023.
//

#include "NetworkShootClient.hpp"

void NetworkShootClient::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::shared_ptr<Network::OwnedMessage> message;

    try {
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkMoveClient System " << e.what() << std::endl;
            return ;
    }
    unsigned int networkId = message->remote;
    auto networkComp = GameEngine::ComponentsType::getComponentType("NetworkClientId");
    auto entitiesPlayers = componentsContainer.getEntitiesWithComponent(networkComp);
    size_t entityId = 0;
    for (auto &entity : entitiesPlayers) {
        auto mayComp = componentsContainer.getComponent(entity, networkComp);
        if (!mayComp.has_value())
            continue;
        auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
        if (netIdComp->id == networkId) {
            std::tuple<unsigned long, int> tuple = {entity, 50};
            eventHandler.queueEvent("SHOOT", tuple);
        }
    }

}