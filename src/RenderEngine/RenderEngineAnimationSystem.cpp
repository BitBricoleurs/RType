//
// Created by Bartosz on 10/24/23.
//

#include "RenderEngineAnimationSystem.hpp"


namespace RenderEngine {
    void RenderEngineAnimationSystem::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) {
        auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("AnimationComponent"));

        for (auto entity : entities) {
            auto animationComponent = std::dynamic_pointer_cast<AnimationComponent>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("AnimationComponent")).value());
            auto spriteComponent = std::dynamic_pointer_cast<SpriteComponent>(componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("SpriteComponent")).value());

            if (animationComponent->currentFrame >= animationComponent->frames.size()) {
                animationComponent->currentFrame = 0;
            }

            spriteComponent->rect1 = animationComponent->frames[animationComponent->currentFrame];

            animationComponent->currentFrame++;
        }
    }
} // namespace RenderEngine