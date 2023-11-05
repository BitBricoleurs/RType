//
// Created by clagasse on 11/1/23.
//

#pragma once

#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "ComponentsType.hpp"
#include "UserGameMode.hpp"
#include "GameState.hpp"

namespace Server {

    class CheckGameEnded : public GameEngine::ISystem {
        public:
            CheckGameEnded() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
            bool _isGameEnded = false;
    };

}
