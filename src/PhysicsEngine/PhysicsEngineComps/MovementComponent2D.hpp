//
// Created by Bartosz on 10/2/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace PhysicsEngine {
    class MovementComponent : public GameEngine::AComponent {
    public:
      MovementComponent() = default;
      ~MovementComponent() override = default;

      size_t getComponentType() override {
        return GameEngine::ComponentsType::getNewComponentType("MovementComponent2D");
      }
    };
} // namespace PhysicsEngine
