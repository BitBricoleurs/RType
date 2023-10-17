//
// Created by Bartosz on 10/17/23.
//

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "AComponent.hpp"


namespace GameEngine {
    class JumpComponent : public AComponent {
    public:
        JumpComponent() = default;
        ~JumpComponent() override = default;

        size_t componentType = ComponentsType::getNewComponentType("JumpComponent");
        bool canJump = true;
        bool isJumping = false;
    private:
    };
}


