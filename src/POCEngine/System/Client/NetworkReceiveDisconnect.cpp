//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkReceiveDisconnect.hpp"

void NetworkReceiveDisconnect::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DISCONNECTING", ids, "", args);
    std::shared_ptr<Network::UserMessage> userMessage = std::make_shared<Network::UserMessage>(0, message);
    eventHandler.queueEvent("SEND_NETWORK", userMessage);
}