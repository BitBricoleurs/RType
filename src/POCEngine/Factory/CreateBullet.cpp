/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateNewBullet
*/

#include "EntityFactory.hpp"

size_t
EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos) {
  size_t entityId = createBullet(container, "assets/11.png", 72, 125, 1, false,
                                 false, pos, GameEngine::Vect2 (-2, 0), 50, true, 0, 1.0f, 0, GameEngine::ColorR(255,255,255,255), 7);

  return entityId;
}

size_t
EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos) {
  size_t entityId = createBullet(container, "assets/mobBullet.png", 6, 28, 4,
                                 false, false, pos, GameEngine::Vect2 (-2, 0), 10, false, 0, 2.5f, 0, GameEngine::ColorR(255,255,255,255), 7);

  eventHandler.scheduleEvent(
      "animate", 10, std::make_tuple(std::string("EnemyBullet"), entityId));
  std::cout << "bullet created" << std::endl;

  return entityId;
}
