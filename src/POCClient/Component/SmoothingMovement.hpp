//
// Created by Clément Lagasse on 27/10/2023.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "Vect2.hpp"

namespace Client {

    class SmoothingMovement : public GameEngine::AComponent {
    public:
        SmoothingMovement(Utils::Vect2 targetPosition):
        _targetPosition(targetPosition){};

        size_t getComponentType() override;

        Utils::Vect2 _targetPosition;
    };
}
