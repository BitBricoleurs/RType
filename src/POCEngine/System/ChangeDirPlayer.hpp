//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "EventHandler.hpp"
#include "IsPlayer.hpp"

class ChangeDirPlayer : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
private:
  bool done = false;
};

