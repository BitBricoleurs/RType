//
// Created by Bartosz on 10/24/23.
//

#include "RenderEngineAnimationSystem.hpp"


namespace RenderEngine {
    void RenderEngineAnimationSystem::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) {

        auto animType = GameEngine::ComponentsType::getComponentType("AnimationComponent");
        auto spriteType = GameEngine::ComponentsType::getComponentType("SpriteComponent");
        auto entities = componentsContainer.getEntitiesWithComponent(animType);

        for (auto entity : entities) {
            auto mayComp = componentsContainer.getComponent(entity, animType);
            auto mayComp2 = componentsContainer.getComponent(entity, spriteType);
            if (!mayComp.has_value() || !mayComp2.has_value())
                continue;

            auto animationComponent = std::static_pointer_cast<AnimationComponent>(mayComp.value());
            auto spriteComponent = std::static_pointer_cast<SpriteComponent>(mayComp2.value());

            if (animationComponent->currentFrame >= animationComponent->frames.size()) {
                animationComponent->currentFrame = 0;
            }

            spriteComponent->rect1 = animationComponent->frames[animationComponent->currentFrame];

            animationComponent->currentFrame++;
        }
    }
} // namespace RenderEngine