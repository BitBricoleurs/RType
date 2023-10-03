//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Utils.hpp"

namespace GameEngine {
    class AccelerationComponent : public AComponent {
    public:
        AccelerationComponent() = default;
        AccelerationComponent(const Vector2& acceleration) : acceleration(acceleration) {}
        ~AccelerationComponent() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("AccelerationComponent"); }
        Vector2 getAcceleration() const { return acceleration; }
        void setAcceleration(const Vector2& acceleration) { this->acceleration = acceleration; }
    private:
        Vector2 acceleration;
    };
}