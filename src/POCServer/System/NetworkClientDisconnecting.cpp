//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkClientDisconnecting.hpp"

void NetworkClientDisconnecting::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::shared_ptr<Network::OwnedMessage> message;

        try {
            message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
        } catch (std::bad_any_cast &e) {
                std::cerr << "Error from NetworkMoveClient System " << e.what() << std::endl;
                return ;
        }
        unsigned int networkId = message->remote;
        auto networkComp = GameEngine::ComponentsType::getComponentType("NetworkClientId");
        auto entitiesPlayers = componentsContainer.getEntitiesWithComponent(networkComp);
        for (auto &entity : entitiesPlayers) {
            auto mayComp = componentsContainer.getComponent(entity, networkComp);
            if (!mayComp.has_value())
                continue;
            auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
            if (netIdComp->id == networkId) {
                auto &server = Network::Server::getInstance();
                server.disconnectClient(networkId);
                componentsContainer.deleteEntity(entity);
                std::vector<size_t> ids = {entity};
                std::vector<std::any> args = {};
                std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", ids, "", args);
                std::shared_ptr<Network::NotUserMessage> notMessage = std::make_shared<Network::NotUserMessage>(netIdComp->id, message);
                eventHandler.queueEvent("SEND_NETWORK", notMessage);
            }
        }

}