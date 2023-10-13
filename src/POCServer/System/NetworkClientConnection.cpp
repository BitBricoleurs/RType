//
// Created by Clément Lagasse on 05/10/2023.
//

#include "NetworkClientConnection.hpp"

void NetworkClientConnection::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    Network::TSQueue<unsigned int> &queue = Network::Server::getInstance().getConnectedClients();
    if (queue.empty())
        return;
    unsigned int netInterfaceId = queue.popBack();
    size_t entityId = componentsContainer.createEntity();
    componentsContainer.bindComponentToEntity(entityId, std::make_shared<NetworkClientId>(netInterfaceId));
    std::vector<size_t> ids = {entityId};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_USER", ids, "", args);
    std::shared_ptr<Network::NotUserMessage> notMessage = std::make_shared<Network::NotUserMessage>(netInterfaceId, message);
    eventHandler.queueEvent("SEND_NETWORK", notMessage);
    std::shared_ptr<Network::Message> message2 = std::make_shared<Network::Message>("ACCEPTED", ids, "", args);
    std::shared_ptr<Network::UserMessage> userMessage = std::make_shared<Network::UserMessage>(netInterfaceId, message2);
    eventHandler.queueEvent("SEND_NETWORK", userMessage);
}