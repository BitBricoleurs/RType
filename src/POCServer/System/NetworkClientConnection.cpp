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
    auto &factory = EntityFactory::getInstance();
    GameEngine::Vect2 pos = {0, 0};
    PlayerNumber nbr = factory.getNextPlayerNumber();
    size_t entityId = factory.createNewPlayer(componentsContainer, eventHandler, pos, nbr);
    auto netComp = std::make_shared<NetworkClientId>(netInterfaceId);
    componentsContainer.bindComponentToEntity(entityId, netComp);
    std::vector<size_t> ids = {entityId};
    std::vector<std::any> args = {static_cast<int>(nbr)};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_USER", ids, "INT", args);
    std::shared_ptr<Network::NotUserMessage> notMessage = std::make_shared<Network::NotUserMessage>(netInterfaceId, message);
    eventHandler.queueEvent("SEND_NETWORK", notMessage);
    std::shared_ptr<Network::Message> message2 = std::make_shared<Network::Message>("ACCEPTED", ids, "INT", args);
    std::shared_ptr<Network::UserMessage> userMessage = std::make_shared<Network::UserMessage>(netInterfaceId, message2);
    eventHandler.queueEvent("SEND_NETWORK", userMessage);
    eventHandler.queueEvent("CREATE_WORLD", entityId);
}