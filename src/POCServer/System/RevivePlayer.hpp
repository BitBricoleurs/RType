//
// Created by clagasse on 11/1/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Health.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "UserGameMode.hpp"

namespace Server {

    class RevivePlayer : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;
    };

}
