//
// Created by clagasse on 10/31/23.
//

#pragma once

#include "ISystem.hpp"
#include "Message.hpp"
#include "PowerUpUtils.hpp"
#include "Vect2.hpp"
#include "EntityFactory.hpp"
#include "UserGameMode.hpp"

namespace Client {

    class DeathPlayer : public GameEngine::ISystem {
    public:
        DeathPlayer() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };

}
