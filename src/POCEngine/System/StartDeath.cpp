/*
** EPITECH PROJECT, 2023
** RType
** File description:
** StartDeath
*/

#include "StartDeath.hpp"

void StartDeath::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {
  std::cout << "start death" << std::endl;
  auto ID = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
  auto velocityOpt = componentsContainer.getComponent(
      ID, GameEngine::ComponentsType::getComponentType("VelocityComponent"));

  auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
      velocityOpt.value());
  velocity->velocity.x = 0;
  velocity->velocity.x = 0;
  componentsContainer.unbindComponentFromEntity(
      ID, GameEngine::ComponentsType::getComponentType("SpriteAnimation"));
  eventHandler.scheduleEvent("MobDeath", 5, ID);
  eventHandler.unscheduleEvent("Death");
  std::cout << "End death" << std::endl;
}