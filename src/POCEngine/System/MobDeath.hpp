//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "DeathAnimation.hpp"

class MobDeathSystem : public GameEngine::ISystem {
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};

