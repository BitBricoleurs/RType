//
// Created by Clément Lagasse on 05/11/2023.
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

    class DeletePowerUp : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    public:

    };
}
