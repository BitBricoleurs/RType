//
// Created by Clément Lagasse on 09/10/2023.
//

#pragma once

#include "Server.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "NetworkClientId.hpp"
#include "VelocityComponent.hpp"
#include "IMessage.hpp"
#include "Shooter.hpp"

namespace Server {

    class NetworkMoveClient : public GameEngine::ISystem {
        public:
            NetworkMoveClient() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;

        private:
            float _speed = 7;

    };
}
