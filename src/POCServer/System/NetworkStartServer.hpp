//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "Server.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"

class NetworkStartServer : public GameEngine::ISystem {
    public:
        NetworkStartServer() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
};

