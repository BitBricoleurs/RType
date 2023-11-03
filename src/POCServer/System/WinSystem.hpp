//
// Created by clagasse on 11/1/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "GameState.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"

namespace Server {
    class WinSystem : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}

