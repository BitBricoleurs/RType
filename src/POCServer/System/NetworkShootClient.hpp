//
// Created by Clément Lagasse on 10/10/2023.
//

#pragma once

#include "Server.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "NetworkClientId.hpp"
#include "IMessage.hpp"
#include "PositionComponent2D.hpp"
#include "BulletCreateStruct.hpp"

class NetworkShootClient : public GameEngine::ISystem {
    public:
        NetworkShootClient() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;

    private:
};

