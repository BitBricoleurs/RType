/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IncreaseDifficulty
*/

#include "IncreaseDifficulty.hpp"

void IncreaseDifficulty::update(
    GameEngine::ComponentsContainer &componentsContainer,
    GameEngine::EventHandler &eventHandler) {

  auto game = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("Game"));
  auto baseVelOpt = componentsContainer.getComponent(
      game, GameEngine::ComponentsType::getComponentType("BaseVelocity"));
  if (baseVelOpt.has_value()) {
    auto baseVel = std::static_pointer_cast<BaseVelocity>(baseVelOpt.value());
    if (baseVel->velocity.x < 16) {
      baseVel->velocity.x += 1;
    }
  }
}