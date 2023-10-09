//
// Created by Clément Lagasse on 04/10/2023.
//

#include "NetworkInput.hpp"

NetworkInput::NetworkInput(Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue) : _forwardQueue(forwardQueue) {}


std::unordered_map<std::string, std::string> NetworkInput::_actionEventMap = {
    {"CONNECT", "NETWORK_CLIENT_CONNECTION"},
    {"ACCEPTED", "NETWORK_SERVER_ACCEPT"},
    {"CREATED_USER", "NETWORK_NEW_CLIENT_CON"},
    {"action2", "event2"}
};

void NetworkInput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (_forwardQueue.empty())
        return;
    while (!_forwardQueue.empty()) {
        auto message = _forwardQueue.popFront();
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(message->message->getMessage());
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