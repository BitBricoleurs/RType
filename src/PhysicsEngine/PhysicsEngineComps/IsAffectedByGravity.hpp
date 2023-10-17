//
// Created by Bartosz on 10/17/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class IsAffectedByGravity : public AComponent {
    public:
        IsAffectedByGravity() = default;
        ~IsAffectedByGravity() override = default;

        size_t componentType = ComponentsType::getNewComponentType("IsAffectedByGravity");
    };
}