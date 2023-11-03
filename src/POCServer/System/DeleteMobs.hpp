//
// Created by clagasse on 11/1/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ComponentContainer.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "IsMob.hpp"

namespace Server {

    class DeleteMobs : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    public:

    };
}
