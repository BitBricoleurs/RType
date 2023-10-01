//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "src/UtilsProject/Utils.hpp"

namespace GameEngine {
    class AccelerationComponent : public AComponent {
    public:
        AccelerationComponent() = default;
        AccelerationComponent(const Vector2& acceleration) : acceleration(acceleration) {}
        ~AccelerationComponent() override = default;

        size_t getComponentType() override { return componentType; }
        Vector2 getAcceleration() const { return acceleration; }
        void setAcceleration(const Vector2& acceleration) { this->acceleration = acceleration; }
    private:
        size_t componentType = ComponentsType::getNewComponentType("AccelerationComponent");
        Vector2 acceleration;
    };
}