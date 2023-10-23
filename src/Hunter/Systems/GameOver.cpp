/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GameOver
*/

#include "GameOver.hpp"

void GameOver::update(GameEngine::ComponentsContainer &componentsContainer,
                      GameEngine::EventHandler &eventHandler) {
  eventHandler.unscheduleEvent("animateShot");
  eventHandler.unscheduleEvent("spawnBird");

  // Remove all bird entities.
  auto birds = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("Bird"));
  for (auto &bird : birds) {
    componentsContainer.deleteEntity(bird);
  }

  // Create an entity for the 'play again' button.
  auto playAgainId = componentsContainer.createEntity();

  // Define the position for the button.
  GameEngine::Vect2 pos(1920 / 2 - (1300 * 0.6f) / 2,
                        1080 / 2 - (1300 * 0.6f) / 2);

  // Create position component.
  auto positionComponent =
      std::make_shared<GameEngine::PositionComponent2D>(pos);

  // Create button component.
  auto buttonComponent = std::make_shared<GameEngine::ButtonComponent>(
      "assets/hunter/gameover.png", pos, GameEngine::rect{0, 0, 1300, 1300}, 3,
      0.6f, 0,
      GameEngine::ColorR{255, 255, 255,
                         255}); // Assuming you have a Color struct or similar.

  buttonComponent->clickEvent = "startNewGame";

  componentsContainer.bindComponentToEntity(playAgainId, positionComponent);
  componentsContainer.bindComponentToEntity(playAgainId, buttonComponent);
}
