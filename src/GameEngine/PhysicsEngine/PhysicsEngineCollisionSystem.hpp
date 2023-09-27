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
        void Update();
    private:
        std::vector<std::pair<size_t , size_t >> potentialCollisions;
    };
}