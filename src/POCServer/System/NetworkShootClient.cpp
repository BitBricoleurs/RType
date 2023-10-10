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

    std::vector<char> argsShoot;
    try {
        argsShoot.push_back(std::any_cast<char>(messageData->getArgs()));
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from NetworkShootClient System Float" << e.what() << std::endl;
        return ;
    }
    bool isShootPower = argsShoot[0] == 1;

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
            auto velocityComp = GameEngine::ComponentsType::getComponentType("VelocityComponent");
            auto mayComp2 = componentsContainer.getComponent(entity, velocityComp);
            if (!mayComp2.has_value())
                continue;
            auto velComp = std::static_pointer_cast<GameEngine::PositionComponent2D>(mayComp2.value());
            pos = velComp->pos;
            entityId = entity;
        }
    }
    bool isPLayerShoot = true;

    GameEngine::Vect2 vel {0, 0};
    BulletCreate bulletCreate = {pos, vel, isPLayerShoot, isShootPower};
    eventHandler.queueEvent("CREATE_BULLET", bulletCreate);
}