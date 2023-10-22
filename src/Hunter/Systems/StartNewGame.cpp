/*
** EPITECH PROJECT, 2023
** RType
** File description:
** StartNewGame
*/

#include "StartNewGame.hpp"

void StartNewGame::update(GameEngine::ComponentsContainer &componentsContainer,
                          GameEngine::EventHandler &eventHandler) {
  eventHandler.scheduleEvent("spawnBird", 120);

  auto scoreId = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("Score"));
  auto scoreOpt = componentsContainer.getComponent(
      scoreId, GameEngine::ComponentsType::getComponentType("Score"));
  auto score = std::dynamic_pointer_cast<Score>(scoreOpt.value());
  score->missed = 0;
  score->_score = 0;
}
