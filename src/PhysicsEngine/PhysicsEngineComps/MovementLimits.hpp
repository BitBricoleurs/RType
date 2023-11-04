//
// Created by Theophilus Homawoo on 04/11/2023.
//

//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Vect2.hpp"
#include "ComponentsType.hpp"

namespace PhysicsEngine {
    class MovementLimits : public GameEngine::AComponent {
    public:
        MovementLimits() = default;
        explicit MovementLimits(const Utils::Vect2& topLeft, const Utils::Vect2& bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {}
        ~MovementLimits() override = default;

        size_t getComponentType() override;
        Utils::Vect2 topLeft;
        Utils::Vect2 bottomRight;
    private:
    };
}

