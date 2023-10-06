//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

// System of the SERVER that handle the timeout of the clients

#include "ISystem.hpp"
#include "Server.hpp"
#include "ComponentContainer.hpp"
#include "EventHandler.hpp"
#include "UserMessage.hpp"
#include "Message.hpp"
#include "NetworkClientId.hpp"

class NetworkClientTimeout : public GameEngine::ISystem {
    public:
        NetworkClientTimeout(std::shared_ptr<Network::Server> &server);
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        std::shared_ptr<Network::Server> _server;

};


