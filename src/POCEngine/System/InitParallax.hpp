//
// Created by alexandre on 06/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"
#include "EventHandler.hpp"
#include "Parallax.hpp"

class InitParallax : public GameEngine::ISystem {
    void update(GameEngine::ComponentsContainer &componentsContainer,
                GameEngine::EventHandler &eventHandler) override;
public:

private:
  bool done = false;
};
