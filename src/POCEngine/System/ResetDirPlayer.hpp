//
// Created by alexandre on 04/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "EventHandler.hpp"
#include "IsPlayer.hpp"

class ResetDirPlayer : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
private:
  bool done = false;
};
