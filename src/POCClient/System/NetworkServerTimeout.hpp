//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

// System from the client that check if the server have somehow timeout

#include "ISystem.hpp"
#include "Client.hpp"
#include "ComponentContainer.hpp"
#include "EventHandler.hpp"
#include "UserMessage.hpp"
#include "Message.hpp"
#include "NetworkClientId.hpp"

class NetworkServerTimeout : public GameEngine::ISystem {
    public:
        NetworkServerTimeout() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
};
