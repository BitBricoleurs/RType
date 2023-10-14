//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkReceiveDisconnect.hpp"

void NetworkReceiveDisconnect::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("DISCONNECTING", ids, "", args);
    eventHandler.queueEvent("SEND_NETWORK", message);
    eventHandler.queueEvent("NETWORK_RECEIVE_DISCONNECT_APPLY", std::any());
}