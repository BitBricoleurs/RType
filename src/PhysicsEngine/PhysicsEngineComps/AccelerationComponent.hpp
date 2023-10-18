//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Vect2.hpp"

namespace PhysicsEngine {
    class AccelerationComponent : public GameEngine::AComponent {
    public:
        AccelerationComponent(const Utils::Vect2& acceleration) : acceleration(acceleration) {}
        ~AccelerationComponent() override = default;

        size_t componentType = GameEngine::ComponentsType::getNewComponentType("AccelerationComponent");
        Utils::Vect2 acceleration;
    private:
    };
}
