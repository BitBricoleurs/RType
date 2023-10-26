//
// Created by alexandre on 26/10/23.
//

#include "NetworkUpdatePosForcePod.hpp"

void Server::NetworkUpdatePosForcePod::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

        auto args = messageData->getArgs();
        std::cout << "Here" << std::endl;
        int playerId = std::any_cast<int>(args[0]);
        std::cout << "This one" << std::endl;
        int forcePodId = std::any_cast<int>(args[1]);
        std::cout << "Pass" << std::endl;
        auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
        auto posPlayer = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
        auto posForcePod = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(forcePodId, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
        auto shooter = std::dynamic_pointer_cast<Shooter>(componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("Shooter")).value());
        auto forcePod = std::dynamic_pointer_cast<IsForcePod>(componentsContainer.getComponent(forcePodId, GameEngine::ComponentsType::getComponentType("IsForcePod")).value());
        auto forcePodVelocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(forcePodId, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
        if (isPlayer->entityIdForcePod == 0) {
            forcePodVelocity->velocity.x = 0;
            isPlayer->entityIdForcePod = forcePodId;
            forcePod->entityId = playerId;
            Utils::Vect2 shootingPosition(posPlayer->pos.x + shooter->shootPosition.x, posPlayer->pos.y + shooter->shootPosition.y - 13);
            posForcePod->pos = shootingPosition;

            //EntityFactory::getInstance().updateEntityNetwork(eventHandler, forcePodId, posForcePod->pos, forcePodVelocity->velocity);
        }
}
