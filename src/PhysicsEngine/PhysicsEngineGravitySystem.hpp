//
// Created by Bartosz on 10/22/23.
//

#pragma once

#include "ISystem.hpp"
#include "PhysicsEngine.hpp"
#include "GravitySystemComponent.hpp"
#include "PositionComponent2D.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "IsOnGroundComponent.hpp"
#include "VelocityComponent.hpp"
#include "ComponentContainer.hpp"


namespace GameEngine {
    class PhysicsEngineGravitySystem : public ISystem {

    public:
        PhysicsEngineGravitySystem() = default;
        ~PhysicsEngineGravitySystem() = default;
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override;
    private:
        std::unique_ptr<PhysicsEngine::PhysicsEngine> physicsEngine;
    };
}
