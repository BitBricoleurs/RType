//
// Created by Bartosz on 10/22/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class IsOnGroundComponent : public AComponent {
    public:
        IsOnGroundComponent() = default;
        ~IsOnGroundComponent() override = default;

        size_t componentType = ComponentsType::getNewComponentType("IsOnGroundComponent");
        bool onGround = false;
    private:
    };
}
