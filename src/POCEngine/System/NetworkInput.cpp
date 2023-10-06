//
// Created by Clément Lagasse on 04/10/2023.
//

#include "NetworkInput.hpp"

NetworkInput::NetworkInput(std::shared_ptr<Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>> &forwardQueue) : _forwardQueue(forwardQueue) {}


void NetworkInput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (_forwardQueue->empty())
        return;
    while (!_forwardQueue->empty()) {
        auto message = _forwardQueue->popFront();
        std::cout << "Message received from : " << message->remote << " data is :" << message->message->getSize() <<std::endl;
    }
}