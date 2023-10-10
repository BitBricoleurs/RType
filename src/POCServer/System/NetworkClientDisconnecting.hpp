//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "NetworkClientId.hpp"
#include "Server.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"

class NetworkClientDisconnecting : public GameEngine::ISystem {
    public:
        NetworkClientDisconnecting() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
};
