/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateOnMove
*/

#include "AnimateOnMove.hpp"

namespace Client {

    void AnimateOnMove::update(GameEngine::ComponentsContainer &componentsContainer,
                               GameEngine::EventHandler &eventHandler) {
        try {
            auto playerID = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
            auto player = componentsContainer.getComponentsFromEntity(playerID);

            auto animationOpt = componentsContainer.getComponent(
                playerID,
                GameEngine::ComponentsType::getComponentType("SpriteAnimation"));

            auto velocityOpt = componentsContainer.getComponent(
                playerID,
                GameEngine::ComponentsType::getComponentType("VelocityComponent"));

            auto spriteOpt = componentsContainer.getComponent(
                playerID,
                GameEngine::ComponentsType::getComponentType("SpriteComponent"));

            if (!animationOpt.has_value() || !velocityOpt.has_value() ||
                !spriteOpt.has_value())
                return;
            auto animation =
                std::static_pointer_cast<SpriteAnimation>(animationOpt.value());
            auto sprite =
                std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteOpt.value());
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(
                velocityOpt.value());

            int toAdd = 0;
            if (animation && sprite && velocity) {
                if (velocity->velocity.y == 0 && animation->currentFrameIndex == 2)
                    return;
                if (velocity->velocity.y == 0) {
                    if (animation->currentFrameIndex < 2) {
                        animation->currentFrameIndex++;
                    }
                    if (animation->currentFrameIndex > 2) {
                        animation->currentFrameIndex--;
                    }
                } else if (velocity->velocity.y > 0 && animation->currentFrameIndex > 0) {
                    animation->currentFrameIndex--;
                } else if (velocity->velocity.y < 0 && animation->currentFrameIndex < 4) {
                    animation->currentFrameIndex++;
                } else {
                    return;
                }
                animation->currentFrame =
                    animation->spritePositionsLeft[animation->currentFrameIndex];
                sprite->rect1.x = animation->currentFrame.x;
                sprite->rect1.y = animation->currentFrame.y;
            }
        } catch (const std::bad_any_cast&) {
            std::cerr << "Cast error in AnimateOnMove::update" << std::endl;
        }
    };

}
