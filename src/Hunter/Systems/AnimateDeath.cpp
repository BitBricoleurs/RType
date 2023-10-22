/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateDeath
*/

#include "AnimateDeath.hpp"

void AnimateDeath::update(GameEngine::ComponentsContainer &componentsContainer,
                          GameEngine::EventHandler &eventHandler) {

  std::cout << "AnimateDeath" << std::endl;
  auto entityID =
      std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
  auto deathOpt = componentsContainer.getComponent(
      entityID, GameEngine::ComponentsType::getComponentType("DeathAnimation"));
  auto spriteOpt = componentsContainer.getComponent(
      entityID,
      GameEngine::ComponentsType::getComponentType("ButtonComponent"));

  if (deathOpt.has_value() && spriteOpt.has_value()) {
    auto sprite = std::dynamic_pointer_cast<GameEngine::ButtonComponent>(
        spriteOpt.value());
    auto deathAnim =
        std::dynamic_pointer_cast<DeathAnimation>(deathOpt.value());

    if (sprite->imagePath != deathAnim->filepath) {
      sprite->rect1.w = deathAnim->frameWidth;
      sprite->rect1.h = deathAnim->frameHeight;
      sprite->imagePath = deathAnim->filepath;
      sprite->scale = 0.3f;
    }
    if (deathAnim->currentFrameIndex == deathAnim->frames) {
      componentsContainer.deleteEntity(entityID);
      eventHandler.unscheduleEvent("animateDeath", entityID);
      return;
    }
    deathAnim->currentFrame =
        deathAnim->spritePositions[deathAnim->currentFrameIndex++];
    sprite->rect1.x = deathAnim->currentFrame.x;
    sprite->rect1.y = deathAnim->currentFrame.y;
  }
}