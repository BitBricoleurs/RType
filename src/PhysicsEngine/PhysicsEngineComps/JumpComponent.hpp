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
        JumpComponent(bool canJump, float jumpStrength, float jumpSpeed) : canJump(canJump), jumpStrength(jumpStrength), jumpSpeed(jumpSpeed) {}
        ~JumpComponent() override = default;

        size_t componentType = ComponentsType::getNewComponentType("JumpComponent");
        bool canJump = true;
        bool isJumping = false;
        float jumpStrength;
        float jumpSpeed;
    private:
    };
}


