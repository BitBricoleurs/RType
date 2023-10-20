/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animate
*/

#include "Animate.hpp"

void Animate::update(GameEngine::ComponentsContainer &componentsContainer,
                     GameEngine::EventHandler &eventHandler) {
  size_t entityID =
      std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

  auto animationOpt = componentsContainer.getComponent(
      entityID, GameEngine::ComponentsType::getComponentType("Animation"));
  auto velocityOpt = componentsContainer.getComponent(
      entityID,
      GameEngine::ComponentsType::getComponentType("VelocityComponent"));
  auto spriteOpt = componentsContainer.getComponent(
      entityID,
      GameEngine::ComponentsType::getComponentType("ButtonComponent"));

  if (animationOpt.has_value() && velocityOpt.has_value() &&
      spriteOpt.has_value()) {

    auto animation = std::dynamic_pointer_cast<Animation>(animationOpt.value());
    auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
        velocityOpt.value());
    auto sprite = std::dynamic_pointer_cast<GameEngine::ButtonComponent>(
        spriteOpt.value());
    if (sprite->isVisible) {
      if (animation->twoDirections && velocity) {
        if (animation->currentFrameIndex >= animation->frames / 2)
          animation->currentFrameIndex = 0;
        if (velocity->velocity.x > 1)
          animation->currentFrame =
              animation->spritePositionsRight[animation->currentFrameIndex++];
        else
          animation->currentFrame =
              animation->spritePositionsLeft[animation->currentFrameIndex++];
      } else {
        if (animation->currentFrameIndex >= animation->frames)
          animation->currentFrameIndex = 0;
        animation->currentFrame =
            animation->spritePositionsLeft[animation->currentFrameIndex++];
      }
      sprite->rect1.x = animation->currentFrame.x;
      sprite->rect1.y = animation->currentFrame.y;
    }
  }
}