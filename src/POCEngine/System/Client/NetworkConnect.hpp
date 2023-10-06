//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "../../../SharedNetwork/Utils/Endpoint.hpp"
#include "Client.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"

class NetworkInitConnection : public GameEngine::ISystem {

public:
    NetworkInitConnection(std::shared_ptr<Network::Client> &client);
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
    private:
        std::shared_ptr<Network::Client> _client;
};

