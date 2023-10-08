//
// Created by alexandre on 03/10/23.
//

#include "UpdateEntitySprite.hpp"

void updateEntitySprite::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {

    auto data = std::any_cast<std::tuple<std::string, size_t>>(eventHandler.getTriggeredEvent().second);
    std::string entityType = std::get<0>(data);
    size_t entityID = std::get<1>(data);
    auto animationOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteAnimation"));
    auto velocityOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
    if (animationOpt.has_value() && velocityOpt.has_value() && spriteOpt.has_value()) {
    auto animation = std::dynamic_pointer_cast<SpriteAnimation>(animationOpt.value());
    auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(velocityOpt.value());
    auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());
        if (sprite->isVisible) {
            if (animation->twoDirections && velocity) {
                if (animation->currentFrameIndex >= animation->frames / 2)
                    animation->currentFrameIndex = 0;
                if (velocity->velocity.x > 1)
                animation->currentFrame = animation->spritePositionsRight[animation->currentFrameIndex++];
                else
                animation->currentFrame = animation->spritePositionsLeft[animation->currentFrameIndex++];
            } else {
                if (animation->currentFrameIndex >= animation->frames)
                    animation->currentFrameIndex = 0;
                animation->currentFrame = animation->spritePositionsLeft[animation->currentFrameIndex++];
            }
            sprite->rect1.x = animation->currentFrame.x;
            sprite->rect1.y = animation->currentFrame.y;
      }
    }
}
