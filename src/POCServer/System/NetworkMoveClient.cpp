//
// Created by Clément Lagasse on 09/10/2023.
//

#include "NetworkMoveClient.hpp"

void NetworkMoveClient::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {
    std::shared_ptr<Network::OwnedMessage> message;

    try {
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkMoveClient System " << e.what() << std::endl;
    }
    unsigned int networkId = message->remote;
    std::shared_ptr<Network::IMessage> IMessage = message->message;
    std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

    GameEngine::Vect2 newVel = {0, 0};
    std::vector<float> argsVel;
    for (auto &arg : messageData->getArgs()) {
        try {
            argsVel.push_back(std::any_cast<float>(arg));
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkMoveClient System " << e.what() << std::endl;
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
            auto velComp = std::static_pointer_cast<GameEngine::VelocityComponent>(mayComp2.value());
            velComp->velocity = newVel;
            entityId = entity;
        }
    }
    std::vector<size_t> ids = {entityId};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::Message> messageOut = std::make_shared<Network::Message>("UPDATE_VELOCITY", ids, "", args);
    std::shared_ptr<Network::AllUsersMessage> userMessage = std::make_shared<Network::AllUsersMessage>(messageOut);
    eventHandler.queueEvent("SEND_NETWORK", userMessage);
}