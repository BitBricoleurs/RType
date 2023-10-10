//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class VelocityComponent : public AComponent {
    public:
        VelocityComponent() = default;
        VelocityComponent(const Vector2& velocity) : velocity(velocity) {}
        ~VelocityComponent() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("VelocityComponent"); }
        Vector2 getVelocity() const { return velocity; }
        void setVelocity(const Vector2& velocity) { this->velocity = velocity; }
    private:
        Vector2 velocity;
    };
}