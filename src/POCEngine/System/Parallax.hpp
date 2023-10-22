//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "IsParallax.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "SpriteComponent.hpp"
#include <algorithm>

class Parallax : public GameEngine::ISystem {
public:
  Parallax() = default;

  ~Parallax() = default;

  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};