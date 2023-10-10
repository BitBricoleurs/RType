//
// Created by Bartosz on 10/2/23.
//

#pragma once

#include "PhysicsEngine.hpp"
#include "PositionComponent2D.hpp"
#include "VelocityComponent.hpp"
#include "MovementComponent2D.hpp"
#include "EventHandler.hpp"
#include "RectangleColliderComponent2D.hpp"

namespace GameEngine {

    class PhysicsEngineMovementSystem2D : public ISystem {
    public:
        PhysicsEngineMovementSystem2D();
        ~PhysicsEngineMovementSystem2D()  = default;

        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler);
    private:
        std::unique_ptr<PhysicsEngine> engine;
    };
}
