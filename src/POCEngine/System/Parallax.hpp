//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "Utils.hpp"
#include "IsParallax.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "SpriteComponent.hpp"

class ParallaxSystem : public GameEngine::ISystem {
public:
  ParallaxSystem() = default;

  ~ParallaxSystem() = default;

  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};