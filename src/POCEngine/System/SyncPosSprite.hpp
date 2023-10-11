//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "PositionComponent2D.hpp"
#include "SpriteComponent.hpp"

class SyncPosSprite : public GameEngine::ISystem {
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
public:

private:
  bool done = false;
};

