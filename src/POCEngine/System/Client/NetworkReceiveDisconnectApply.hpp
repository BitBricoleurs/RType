//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "Client.hpp"

// Last system to be executed because it's cutting the connection with the server and the client

class NetworkReceiveDisconnectApply : public GameEngine::ISystem {
    public:
        NetworkReceiveDisconnectApply(std::shared_ptr<Network::Client> &client);
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        std::shared_ptr<Network::Client> _client;

};

