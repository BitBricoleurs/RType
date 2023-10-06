//
// Created by Clément Lagasse on 05/10/2023.
//

#include "NetworkClientConnection.hpp"

void NetworkClientConnect::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    unsigned int netInterfaceId = 0;

    try {
        netInterfaceId = std::any_cast<unsigned int>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
    }
    size_t entityId = componentsContainer.createEntity();
    componentsContainer.bindComponentToEntity(entityId, std::make_shared<NetworkClientId>(netInterfaceId));
    std::vector<size_t> ids = {entityId};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_USER", ids, "", args);
    std::shared_ptr<Network::NotUserMessage> notMessage = std::make_shared<Network::NotUserMessage>(netInterfaceId, message);
    eventHandler.queueEvent("SEND_NETWORK", notMessage);
}