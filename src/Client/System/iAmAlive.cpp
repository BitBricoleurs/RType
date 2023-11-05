//
// Created by Clément Lagasse on 27/10/2023.
//

#include "iAmAlive.hpp"

void Client::iAmAlive::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("ALIVE", ids, "", args);
    eventHandler.queueEvent("SEND_NETWORK", message);
}