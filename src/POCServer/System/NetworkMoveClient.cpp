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

                auto isPlayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
                auto compPlayer = componentsContainer.getComponent(entity, isPlayerType);
                if (!compPlayer.has_value())
                    continue;
                auto isPlayer = std::static_pointer_cast<IsPlayer>(compPlayer.value());
                if (isPlayer->entityIdForcePod != 0) {

                    auto velType = GameEngine::ComponentsType::getComponentType("VelocityComponent");
                    auto shooterType = GameEngine::ComponentsType::getComponentType("Shooter");
                    auto posType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
                    auto netType = GameEngine::ComponentsType::getComponentType("NetworkClientId");

                    auto velOpt = componentsContainer.getComponent(entity, velType);
                    auto shooterOpt = componentsContainer.getComponent(entity, shooterType);
                    auto posPlayerOpt = componentsContainer.getComponent(entity, posType);
                    auto posForcePodOpt = componentsContainer.getComponent(isPlayer->entityIdForcePod, posType);
                    auto velForcePodOpt = componentsContainer.getComponent(isPlayer->entityIdForcePod, velType);
                    auto netOpt = componentsContainer.getComponent(entity, netType);

                    if (!velOpt.has_value() || !shooterOpt.has_value() || !posPlayerOpt.has_value() || !posForcePodOpt.has_value() || !netOpt.has_value())
                        return;


                    auto forcePodVelocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velForcePodOpt.value());
                    auto shooter = std::static_pointer_cast<Shooter>(shooterOpt.value());
                    auto posPlayer = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posPlayerOpt.value());
                    auto posForcePod = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posForcePodOpt.value());
                    forcePodVelocity->velocity.x = newVel.x;
                    forcePodVelocity->velocity.y = newVel.y;
                    Utils::Vect2 shootingPosition(posPlayer->pos.x + shooter->shootPosition.x - 45, posPlayer->pos.y + shooter->shootPosition.y - 13);
                    posForcePod->pos = shootingPosition;
                    auto network = std::static_pointer_cast<NetworkClientId>(netOpt.value());
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
                 EntityFactory::getInstance().updateEntityNetworkWithVelocity(eventHandler, entityId, newVel);
            }
        }
    }
}