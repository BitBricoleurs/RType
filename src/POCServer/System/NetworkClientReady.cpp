//
// Created by Clément Lagasse on 23/10/2023.
//

#include "NetworkClientReady.hpp"

void Server::NetworkClientReady::update(GameEngine::ComponentsContainer &componentsContainer,
                                        GameEngine::EventHandler &eventHandler)
{
    std::shared_ptr<Network::OwnedMessage> message;

    try {
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from ClientReady System " << e.what() << std::endl;
        return ;
    }
    unsigned int networkId = message->remote;
    auto networkComp = GameEngine::ComponentsType::getComponentType("NetworkClientId");
    auto entitiesPlayers = componentsContainer.getEntitiesWithComponent(networkComp);
    EntityFactory &factory = EntityFactory::getInstance();
    for (auto &entity : entitiesPlayers) {
        auto mayComp = componentsContainer.getComponent(entity, networkComp);
        if (!mayComp.has_value())
            continue;
        auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
        if (netIdComp->id == networkId) {
            std::shared_ptr<GameEngine::IComponent> isReady = std::make_shared<Server::IsReady>();
            componentsContainer.bindComponentToEntity(entity, isReady);
            eventHandler.queueEvent("CHECK_EVERY_CLIENT_READY", std::any());
        }
    }
}