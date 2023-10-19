//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include <vector>
#include <iostream>
#include "ISystem.hpp"
#include "PhysicsEngine.hpp"
#include "AABBComponent2D.hpp"
#include "AColliderComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "PositionComponent2D.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"

namespace PhysicsEngine
{
    class PhysicsEngineCollisionSystem2D : public GameEngine::ISystem
    {
    public:
        PhysicsEngineCollisionSystem2D();
        ~PhysicsEngineCollisionSystem2D();
        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override;
    private:
        std::vector<std::pair<size_t , size_t >> potentialCollisions;
        std::unique_ptr<PhysicsEngine> physicsEngine;
    };
}
