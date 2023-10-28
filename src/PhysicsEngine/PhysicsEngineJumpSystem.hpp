//
// Created by Bartosz on 10/17/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "JumpComponent.hpp"
#include "IsOnGroundComponent.hpp"
#include "GravityComponent.hpp"
#include "VelocityComponent.hpp"
#include "ComponentsType.hpp"
#include "ComponentContainer.hpp"
#include "PhysicsEngine.hpp"


namespace PhysicsEngine {

    class JumpSystem : public GameEngine::ISystem {
    public:
        JumpSystem() = default;
        ~JumpSystem() = default;

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override {
            while (!eventHandler.getTriggeredEvent().first.empty() && eventHandler.getTriggeredEvent().first == "Jump") {
                auto entity = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

                auto jumpComp = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("JumpComponent"));
                auto isOnGround1 = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("IsOnGroundComponent"));

                auto jump = std::dynamic_pointer_cast<JumpComponent>(*jumpComp);
                auto isOnGround = std::dynamic_pointer_cast<IsOnGroundComponent>(*isOnGround1);

                if (isOnGround->onGround && jump->canJump) {

                    auto gravity1 = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("GravityComponent"));
                    auto gravity = std::dynamic_pointer_cast<GravityComponent>(*gravity1);
                    size_t jumpDuration = calculateJumpDuration(gravity->baseGravity, jump->jumpStrength);

                    eventHandler.scheduleEvent("ContinueJump", 1, std::make_pair(entity, jumpDuration));

                    jump->isJumping = true;
                    jump->canJump = false;
                }
            }

            while (!eventHandler.getTriggeredEvent().first.empty() && eventHandler.getTriggeredEvent().first == "ContinueJump") {
                auto [entity, jumpDuration] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);

                auto velocity1 = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
                auto jumpComp = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("JumpComponent"));

                auto velocity = std::dynamic_pointer_cast<VelocityComponent>(*velocity1);
                auto jump = std::dynamic_pointer_cast<JumpComponent>(*jumpComp);

                physicsEngine->applyJumpForce(*velocity, jump->jumpSpeed);
                jumpDuration--;
                if (jumpDuration == 0) {
                    jump->isJumping = false;
                    jump->canJump = true;
                    eventHandler.unscheduleEvent("ContinueJump", std::make_pair(entity, jumpDuration));
                }
            }
        }

    private:
        size_t calculateJumpDuration(const Utils::Vect2& baseGravity, float jumpStrength) {
            return static_cast<size_t>(-baseGravity.y * jumpStrength);
        }
        std::unique_ptr<PhysicsEngine> physicsEngine;
        size_t jumpDuration = 0;
    };
}


