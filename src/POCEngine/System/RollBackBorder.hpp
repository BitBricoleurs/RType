//
// Created by alexandre on 09/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "EventHandler.hpp"
#include "IsPlayer.hpp"
#include "PositionComponent2D.hpp"
#include "VelocityComponent.hpp"
#include "WindowInfoComponent.hpp"

class RollBackBorder : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
private:
  bool done = false;
};
