//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include <vector>
#include <iostream>
#include "ISystem.hpp"

namespace GameEngine
{
    class PhysicsEngineCollisionSystem : public ISystem
    {
    public:
        PhysicsEngineCollisionSystem() = default;
        ~PhysicsEngineCollisionSystem();
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override;
    private:
        std::vector<std::pair<size_t , size_t >> potentialCollisions;
    };
}