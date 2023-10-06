//
// Created by Clément Lagasse on 05/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "NetworkClientId.hpp"

class NetworkClientRequestDisconnect : public  GameEngine::ISystem {
    public:
        NetworkClientRequestDisconnect() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
};

