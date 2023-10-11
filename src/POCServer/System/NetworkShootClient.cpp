//
// Created by Clément Lagasse on 10/10/2023.
//

#include "NetworkShootClient.hpp"

void NetworkShootClient::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::shared_ptr<Network::OwnedMessage> message;

    try {
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkMoveClient System " << e.what() << std::endl;
    }
    unsigned int networkId = message->remote;
    std::shared_ptr<Network::IMessage> IMessage = message->message;
    std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

    GameEngine::Vect2 pos {0, 0};
    auto networkComp = GameEngine::ComponentsType::getComponentType("NetworkClientId");
    auto entitiesPlayers = componentsContainer.getEntitiesWithComponent(networkComp);
    size_t entityId = 0;
    for (auto &entity : entitiesPlayers) {
        auto mayComp = componentsContainer.getComponent(entity, networkComp);
        if (!mayComp.has_value())
            continue;
        auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
        if (netIdComp->id == networkId) {
            auto shooterComp = GameEngine::ComponentsType::getComponentType("Shooter");
            auto mayComp2 = componentsContainer.getComponent(entity, shooterComp);
            if (!mayComp2.has_value())
                continue;
            auto shooter = std::static_pointer_cast<Shooter>(mayComp2.value());
            pos = shooter->shootPosition;
            entityId = entity;
        }
    }
    bool isShootPower = true;
    EntityFactory &factory = EntityFactory::getInstance();
    GameEngine::Vect2 velocity {2, 2};
    factory.createPlayerBullet(componentsContainer, eventHandler, pos, velocity, isShootPower);
}