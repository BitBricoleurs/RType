//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "Health.hpp"
#include "ComponentsType.hpp"
#include "Damage.hpp"

class updateHealth : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};