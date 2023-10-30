//
// Created by Bartosz on 10/22/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace PhysicsEngine {
    class IsOnGroundComponent : public GameEngine::AComponent {
    public:
        IsOnGroundComponent() = default;
        ~IsOnGroundComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("IsOnGroundComponent");
        }
        bool onGround = false;
    private:
    };
}
