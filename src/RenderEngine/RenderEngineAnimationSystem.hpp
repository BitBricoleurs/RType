//
// Created by Bartosz on 10/24/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "AnimationComponent.hpp"
#include "SpriteComponent.hpp"

namespace RenderEngine {
    class RenderEngineAnimationSystem : public GameEngine::ISystem {
    public:
        RenderEngineAnimationSystem() = default;
        ~RenderEngineAnimationSystem() = default;

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) override;
    };
}