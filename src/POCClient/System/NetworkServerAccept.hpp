//
// Created by Clément Lagasse on 08/10/2023.
//

#pragma once

#include "UserMessage.hpp"
#include "Message.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "IsPlayer.hpp"
#include "EntityFactory.hpp"
#include "GameState.hpp"

namespace Client {

    class NetworkServerAccept : public GameEngine::ISystem {
        public:
            NetworkServerAccept() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:

    };

}
