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
                velComp->velocity.x += newVel.x;
                velComp->velocity.y += newVel.y;
                newVel = velComp->velocity;
                entityId = entity;
                auto shooterTypes = GameEngine::ComponentsType::getComponentType("Shooter");
                auto compShooter = componentsContainer.getComponent(entity, shooterTypes);
                if (compShooter.has_value()) {
                    auto IShooter = compShooter.value();
                    auto shooterComp = std::static_pointer_cast<Shooter>(IShooter);
                    shooterComp->velocity.x += newVel.x;
                    shooterComp->velocity.y += newVel.y;
                }
            }
        std::vector<size_t> ids = {entityId};
        std::vector<std::any> args = {newVel.x, newVel.y};
        std::shared_ptr<Network::Message> messageOut = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "FLOAT", args);
        std::shared_ptr<Network::NotUserMessage> userMessage = std::make_shared<Network::NotUserMessage>(networkId, messageOut);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
    }
    }
}