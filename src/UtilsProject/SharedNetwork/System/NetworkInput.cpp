//
// Created by Clément Lagasse on 04/10/2023.
//

#include "NetworkInput.hpp"

NetworkInput::NetworkInput(Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue) : _forwardQueue(forwardQueue) {}

void NetworkInput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (_forwardQueue.empty())
        return;
    while (!_forwardQueue.empty()) {
        auto message = _forwardQueue.popFront();
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(message->message->getMessage());
        std::string action = messageData->getAction();
        if (action.empty())
            continue;
        eventHandler.queueEvent(action, message);
    }
}