//
// Created by Bartosz on 10/17/23.
//

#pragma once

#include "ISystem.hpp"

namespace GameEngine {
    class PhysicsEngineJumpSystem : public ISystem {
    public:
        PhysicsEngineJumpSystem() = default;
        ~PhysicsEngineJumpSystem() = default;

        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler);
    };
}

