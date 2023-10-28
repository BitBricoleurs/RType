//
// Created by Clément Lagasse on 23/10/2023.
//

#pragma once

#include "IsReady.hpp"
#include "NetworkClientId.hpp"
#include "Server.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "EntityFactory.hpp"
#include "GameState.hpp"

namespace Server {

    class CheckEveryClientReady : public GameEngine::ISystem {
        public:
            CheckEveryClientReady() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
    };

}