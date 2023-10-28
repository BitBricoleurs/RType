//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "Endpoint.hpp"
#include "Client.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "Message.hpp"

namespace Client {

class NetworkConnect : public GameEngine::ISystem {

public:
    NetworkConnect() = default;
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
    private:
};

}
