//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkReceiveDisconnectApply.hpp"

namespace Client {

    void NetworkReceiveDisconnectApply::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        Network::Client::getInstance().disconnect();
    }
}
