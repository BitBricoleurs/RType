//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkServerTimeout.hpp"

namespace Client {

    void NetworkServerTimeout::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        bool timedOut = false;
        timedOut = Network::Client::getInstance().isServerTimeout();
        if (timedOut) {
            Network::Client::getInstance().disconnect();
            eventHandler.queueEvent("gameEngineChangeScene", std::string("ConnectScreen"));
        }
    }
}
