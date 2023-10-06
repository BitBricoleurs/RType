//
// Created by Clément Lagasse on 04/10/2023.
//

#include "NetworkInput.hpp"

NetworkInput::NetworkInput(std::shared_ptr<Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>> &forwardQueue) : _forwardQueue(forwardQueue) {}


std::unordered_map<std::string, std::string> NetworkInput::_actionEventMap = {
    {"action1", "event1"},
    {"action2", "event2"}
};

void NetworkInput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (_forwardQueue->empty())
        return;
    while (!_forwardQueue->empty()) {
        auto message = _forwardQueue->popFront();
        auto messageData = std::static_pointer_cast<Network::Message>(message->message);
        auto action = messageData->getAction();
        auto it = _actionEventMap.find(action);
        if (it != _actionEventMap.end()) {
            std::cout << "Action: " << action << " corresponds to Event: " << it->second << std::endl;
            eventHandler.queueEvent(it->second, message);
        } else {
            std::cout << "Action: " << action << " not found in the map." << std::endl;
        }
    }
}