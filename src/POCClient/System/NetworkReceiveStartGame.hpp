//
// Created by Clément Lagasse on 23/10/2023.
//

#pragma once

#pragma once

#include "UserMessage.hpp"
#include "Message.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "IsPlayer.hpp"
#include "EntityFactory.hpp"
#include "GameState.hpp"

namespace Client {

    class NetworkReceiveStartGame : public GameEngine::ISystem {
        public:
            NetworkReceiveStartGame() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:

    };
}
