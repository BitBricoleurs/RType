/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateShot
*/

#include "AnimateShot.hpp"

void AnimateShot::update(GameEngine::ComponentsContainer &componentsContainer,
                         GameEngine::EventHandler &eventHandler) {
  auto entityID = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("Shooter"));
  auto animationOpt = componentsContainer.getComponent(
      entityID, GameEngine::ComponentsType::getComponentType("Animation"));
  auto spriteOpt = componentsContainer.getComponent(
      entityID,
      GameEngine::ComponentsType::getComponentType("SpriteComponent"));

  std::cout << "entityID = " << entityID << std::endl;

  std::cout << "animationOpt.has_value() = " << animationOpt.has_value()
            << std::endl;
  std::cout << "spriteOpt.has_value() = " << spriteOpt.has_value() << std::endl;

  if (animationOpt.has_value() && spriteOpt.has_value()) {
    std::cout << "hasValues" << std::endl;
    auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(
        spriteOpt.value());
    auto animation = std::dynamic_pointer_cast<Animation>(animationOpt.value());

    if (animation->currentFrameIndex == animation->frames) {
      animation->currentFrameIndex = 0;
      animation->currentFrame =
          animation->spritePositionsLeft[animation->currentFrameIndex++];
      sprite->rect1.x = animation->currentFrame.x;
      sprite->rect1.y = animation->currentFrame.y;
      eventHandler.unscheduleEvent("animateShot");
      return;
    }
    animation->currentFrame =
        animation->spritePositionsLeft[animation->currentFrameIndex++];
    sprite->rect1.x = animation->currentFrame.x;
    sprite->rect1.y = animation->currentFrame.y;
  }
}