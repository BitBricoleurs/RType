//
// Created by Bartosz on 10/9/23.
//

#pragma once

#include "ComponentsType.hpp"
#include "Damage.hpp"
#include "EventHandler.hpp"
#include "Health.hpp"
#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"

class MobHit : public GameEngine::ISystem {
public:
    void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

  private:
    void startMobDeath(GameEngine::ComponentsContainer &componentsContainer,
                       GameEngine::EventHandler &eventHandler, size_t id);
};