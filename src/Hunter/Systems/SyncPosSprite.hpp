//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ButtonComponent.hpp"
#include "ISystem.hpp"
#include "PositionComponent2D.hpp"

class SyncPosSprite : public GameEngine::ISystem {
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
