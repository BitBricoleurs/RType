//
// Created by alexandre on 28/10/23.
//

#include "NetworkClientBlockWall.hpp"

void Server::NetworkClientBlockWall::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

        Utils::Vect2 newVel = {0, 0};
        Utils::Vect2 newPos = {0, 0};
        std::vector<float> argsVel;
        for (auto &arg : messageData->getArgs()) {
            try {
                argsVel.push_back(std::any_cast<float>(arg));
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from NetworkMoveClient System Float" << e.what() << std::endl;
                return ;
            }
        }
        if (argsVel.size() != 4)
            return ;
        newVel.x = argsVel[0];
        newVel.y = argsVel[1];
        newPos.x = argsVel[2];
        newPos.y = argsVel[3];
        auto networkComp = GameEngine::ComponentsType::getComponentType("NetworkClientId");
        auto entitiesPlayers = componentsContainer.getEntitiesWithComponent(networkComp);
        for (auto &entity : entitiesPlayers) {
            auto netIdComp = std::static_pointer_cast<NetworkClientId>(componentsContainer.getComponent(entity, networkComp).value());
            if (netIdComp->id == networkId) {
                auto velocityComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
                auto positionComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
                velocityComp->velocity.x = newVel.x;
                velocityComp->velocity.y = newVel.y;
                positionComp->pos.x = newPos.x;
                positionComp->pos.y = newPos.y;

            EntityFactory::getInstance().updateEntityNetwork(eventHandler, entity, positionComp->pos, velocityComp->velocity);
            }
        }
}