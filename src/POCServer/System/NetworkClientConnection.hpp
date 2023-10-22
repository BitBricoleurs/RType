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
#include "EntityFactory.hpp"

namespace Server {

    class NetworkClientConnection : public  GameEngine::ISystem {
        public:
            NetworkClientConnection() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
    };
}
