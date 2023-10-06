//
// Created by Clément Lagasse on 04/10/2023.
//

#pragma once

#include "EventHandler.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "ISystem.hpp"
#include "IMessage.hpp"
#include "UserMessage.hpp"
#include "NetworkClientId.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"

class NetworkOutput : public GameEngine::ISystem {
public:
    enum SystemType {
        CLIENT,
        SERVER
    };

    NetworkOutput(std::shared_ptr<Network::Client> &client);
    NetworkOutput(std::shared_ptr<Network::Server> &server);
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
    private:
        std::shared_ptr<Network::Client> _client;
        std::shared_ptr<Network::Server> _server;
        enum SystemType _type;
};
