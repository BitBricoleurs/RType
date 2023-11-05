/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Shoot
*/

#include "Shoot.hpp"

void Shoot::update(GameEngine::ComponentsContainer &componentsContainer,
                   GameEngine::EventHandler &eventHandler) {
  eventHandler.unscheduleEvent("animateShot");

  auto entityID = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("Shooter"));

  auto animationOpt = componentsContainer.getComponent(
      entityID, GameEngine::ComponentsType::getComponentType("Animation"));
  auto spriteOpt = componentsContainer.getComponent(
      entityID,
      GameEngine::ComponentsType::getComponentType("SpriteComponent"));

  if (animationOpt.has_value() && spriteOpt.has_value()) {
    auto sprite = std::static_pointer_cast<RenderEngine::SpriteComponent>(
        spriteOpt.value());
    auto animation = std::static_pointer_cast<Animation>(animationOpt.value());
    animation->currentFrameIndex = 0;
    animation->currentFrame =
        animation->spritePositionsLeft[animation->currentFrameIndex++];
    sprite->rect1.x = animation->currentFrame.x;
    sprite->rect1.y = animation->currentFrame.y;
  }
  eventHandler.queueEvent("PLAY_SOUND", entityID);

  eventHandler.scheduleEvent("animateShot", 5);
}
