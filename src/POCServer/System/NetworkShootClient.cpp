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
    std::shared_ptr<Network::IMessage> IMessage = message->message;
    std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

    auto networkComp = GameEngine::ComponentsType::getComponentType("NetworkClientId");
    auto entitiesPlayers = componentsContainer.getEntitiesWithComponent(networkComp);

    size_t entityId = 0;
    std::vector<int> argsVel;
    for (auto &arg : messageData->getArgs()) {
        try {
            argsVel.push_back(std::any_cast<int>(arg));
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkMoveClient System Float" << e.what() << std::endl;
            return ;
        }
    }
    BulletTypeEntity type = static_cast<BulletTypeEntity>(argsVel[0]);
    int charge = argsVel[1];
    std::cout << "type" << type << ":" << charge << std::endl;
    for (auto &entity : entitiesPlayers) {
        auto mayComp = componentsContainer.getComponent(entity, networkComp);
        if (!mayComp.has_value())
            continue;
        auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
        if (netIdComp->id == networkId) {
            std::tuple<unsigned long, int> tuple = {entity, charge};
            auto shooterOpt = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("Shooter"));
            if (shooterOpt.has_value()) {
                auto shooterComp = std::static_pointer_cast<Shooter>(shooterOpt.value());
                shooterComp->typeBullet = type;
            }
            eventHandler.queueEvent("SHOOT", tuple);
        }
    }

}
