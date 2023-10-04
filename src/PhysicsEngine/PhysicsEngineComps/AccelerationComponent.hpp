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
        AccelerationComponent(const Vect2& acceleration) : acceleration(acceleration) {}
        ~AccelerationComponent() override = default;

        size_t componentType = ComponentsType::getNewComponentType("AccelerationComponent");
        Vect2 acceleration;
    private:
    };
}
