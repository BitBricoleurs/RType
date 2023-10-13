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

    NetworkOutput(SystemType type);
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
    private:
        enum SystemType _type;
};
