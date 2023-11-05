//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Vect2.hpp"

namespace PhysicsEngine {
    class VelocityComponent : public GameEngine::AComponent {
    public:
        VelocityComponent() = delete;
        explicit VelocityComponent(const Utils::Vect2 &velocity) : velocity(velocity) {}
        ~VelocityComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("VelocityComponent");
        }
        Utils::Vect2 velocity = {0, 0};
};
} // namespace GameEngine