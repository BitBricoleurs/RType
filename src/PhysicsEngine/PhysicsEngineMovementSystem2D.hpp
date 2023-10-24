//
// Created by Bartosz on 10/2/23.
//

#pragma once

#include "EventHandler.hpp"
#include "MovementComponent2D.hpp"
#include "PhysicsEngine.hpp"
#include "PositionComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "Vect2.hpp"
#include "VelocityComponent.hpp"

namespace PhysicsEngine {

class PhysicsEngineMovementSystem2D : public GameEngine::ISystem {
public:
  PhysicsEngineMovementSystem2D();
  ~PhysicsEngineMovementSystem2D() = default;

  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;

private:
  std::unique_ptr<PhysicsEngine> engine;
};
} // namespace PhysicsEngine
