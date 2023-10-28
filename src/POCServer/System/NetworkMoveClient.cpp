//
// Created by Clément Lagasse on 09/10/2023.
//

#include "NetworkMoveClient.hpp"

namespace Server {

    void NetworkMoveClient::update(GameEngine::ComponentsContainer &componentsContainer,
                            GameEngine::EventHandler &eventHandler) {
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

        Utils::Vect2 newVel = {0, 0};
        std::vector<float> argsVel;
        for (auto &arg : messageData->getArgs()) {
            try {
                argsVel.push_back(std::any_cast<float>(arg));
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from NetworkMoveClient System Float" << e.what() << std::endl;
                return ;
            }
        }
        if (argsVel.size() != 2)
            return ;
        newVel.x = argsVel[0];
        newVel.y = argsVel[1];
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
                auto velComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayComp2.value());
                velComp->velocity.x = newVel.x;
                velComp->velocity.y = newVel.y;
                newVel = velComp->velocity;
                entityId = entity;
                auto shooterTypes = GameEngine::ComponentsType::getComponentType("Shooter");
                auto compShooter = componentsContainer.getComponent(entity, shooterTypes);
                if (compShooter.has_value()) {
                    auto IShooter = compShooter.value();
                    auto shooterComp = std::static_pointer_cast<Shooter>(IShooter);
                    shooterComp->velocity.x = newVel.x;
                    shooterComp->velocity.y = newVel.y;
                }

                auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
                if (isPlayer->entityIdForcePod != 0) {
                    auto forcePodVelocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(isPlayer->entityIdForcePod, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
                    auto shooter = std::dynamic_pointer_cast<Shooter>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("Shooter")).value());
                    auto posPlayer = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
                    auto posForcePod = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(isPlayer->entityIdForcePod, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
                    forcePodVelocity->velocity.x = newVel.x;
                    forcePodVelocity->velocity.y = newVel.y;
                    Utils::Vect2 shootingPosition(posPlayer->pos.x + shooter->shootPosition.x - 45, posPlayer->pos.y + shooter->shootPosition.y - 13);
                    posForcePod->pos = shootingPosition;
                    auto network = std::dynamic_pointer_cast<NetworkClientId>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("NetworkClientId")).value());
                    std::vector<size_t> ids = {isPlayer->entityIdForcePod};
                    std::vector<std::any> args = {};
                    args.push_back(posForcePod->pos.x);
                    args.push_back(posForcePod->pos.y);
                    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("UPDATE_POSITION", ids, "FLOAT", args);
                    std::shared_ptr<Network::NotUserMessage> allUserMsg = std::make_shared<Network::NotUserMessage>(network->id, message);
                    eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
                    args.clear();
                    args.push_back(forcePodVelocity->velocity.x);
                    args.push_back(forcePodVelocity->velocity.y);
                    message = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
                    allUserMsg = std::make_shared<Network::NotUserMessage>(network->id, message);
                    eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
                }
            }
            EntityFactory::getInstance().updateEntityNetworkWithVelocity(eventHandler, entityId, newVel);
        }
    }
}