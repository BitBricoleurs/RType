//
// Created by clagasse on 11/1/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ComponentContainer.hpp"
#include "IsParallax.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"

namespace Server {

    class DeleteParallax : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    public:

    };
}
