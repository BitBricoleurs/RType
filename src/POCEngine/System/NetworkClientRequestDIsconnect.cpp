//
// Created by Clément Lagasse on 05/10/2023.
//

#include "NetworkClientRequestDisconnect.hpp"

void NetworkClientRequestDisconnect::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    size_t entityId = 0;

        try {
            entityId = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
        }
        size_t componentType = GameEngine::ComponentsType::getComponentType("NetworkClientId");
        auto mayComp = componentsContainer.getComponent(entityId, componentType);
        if (!mayComp.has_value())
            return;
        auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
        std::vector<size_t> ids = {netIdComp->id};
        std::vector<std::any> args = {};
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DISCONNECT_USER", ids, "", args);
        std::shared_ptr<Network::UserMessage> userMessage = std::make_shared<Network::UserMessage>(entityId, message);
        eventHandler.queueEvent("SEND_NETWORK", userMessage);
}