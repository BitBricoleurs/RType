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
        AccelerationComponent(const Vect2& acceleration) : acceleration(acceleration) {}
        ~AccelerationComponent() override = default;

        size_t getComponentType() override { return componentType; }
        Vect2 getAcceleration() const { return acceleration; }
        void setAcceleration(const Vect2& acceleration) { this->acceleration = acceleration; }
    private:
        size_t componentType = ComponentsType::getNewComponentType("AccelerationComponent");
        Vect2 acceleration;
    };
}