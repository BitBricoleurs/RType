//
// Created by Clément Lagasse on 05/10/2023.
//

#pragma once

#include "Server.hpp"
#include "NetworkClientId.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "IMessage.hpp"

// System of the Server that Handle Client Connection

class NetworkClientConnection : public  GameEngine::ISystem {
    public:
        NetworkClientConnection(std::shared_ptr<Network::Server> &server);
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        std::shared_ptr<Network::Server> _server;
};


