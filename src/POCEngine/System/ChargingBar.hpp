//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "AComponent.hpp"
#include "SpriteComponent.hpp"

class ChargingBar : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;

private:
  int _charge = 0;
  int _maxCharge = 103;
};
