//
// Created by Bartosz on 10/9/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Health.hpp"
#include "Damage.hpp"
#include "VelocityComponent.hpp"

namespace Server {

    class PlayerHitMob : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;
    private:
        void startMobDeath(GameEngine::ComponentsContainer &componentsContainer,
                           GameEngine::EventHandler &eventHandler, size_t id);
    };

}