/*
** EPITECH PROJECT, 2023
** RType
** File description:
** DetectLifeLost
*/

#include "DetectLifeLost.hpp"

void DetectLifeLost::update(
    GameEngine::ComponentsContainer &componentsContainer,
    GameEngine::EventHandler &eventHandler) {

  auto birds = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("Bird"));

  auto scoreId = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("Score"));
  auto scoreOpt = componentsContainer.getComponent(
      scoreId, GameEngine::ComponentsType::getComponentType("Score"));
  if (!scoreOpt.has_value())
    return;
  auto score = std::static_pointer_cast<Score>(scoreOpt.value());

  for (auto &bird : birds) {

    auto birdVelocityOpt = componentsContainer.getComponent(
        bird,
        GameEngine::ComponentsType::getComponentType("VelocityComponent"));

    auto birdPosOpt = componentsContainer.getComponent(
        bird,
        GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

    if (!birdVelocityOpt.has_value() || !birdPosOpt.has_value())
      continue;

    auto birdVelocity =
        std::static_pointer_cast<PhysicsEngine::VelocityComponent>(
            birdVelocityOpt.value());
    auto birdPos =
        std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(
            birdPosOpt.value());

    if (birdVelocity->velocity.x > 0 && birdPos->pos.x > 1920 ||
        birdVelocity->velocity.x < 0 && birdPos->pos.x < -100) {
      componentsContainer.deleteEntity(bird);
      score->missed += 1;
      std::cout << "missed: " << score->missed << std::endl;
    }
    if (score->missed >= 5) {
      eventHandler.queueEvent("gameOver");
      return;
    }
  }
}