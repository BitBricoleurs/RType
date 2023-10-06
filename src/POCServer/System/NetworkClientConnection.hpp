//
// Created by Clément Lagasse on 05/10/2023.
//

#pragma once

#include "NetworkClientId.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"

// System of the Server that Handle Client Connection

class NetworkClientConnection : public  GameEngine::ISystem {
    public:
        NetworkClientConnection() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
};


