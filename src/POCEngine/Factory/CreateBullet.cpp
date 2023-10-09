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
                                  GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {
  size_t entityId = createBullet(container, "assets/11.png", 72, 125, 1, false,
                                 false, pos, velocity, 50, true, 1.0f);

  return entityId;
}

size_t
EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos,
                                     GameEngine::Vect2 velocity) {
  size_t entityId = createBullet(container, "assets/mobBullet.png", 6, 28, 4,
                                 false, false, pos, velocity, 10, false, 2.5f);

  eventHandler.scheduleEvent(
      "animate", 10, std::make_tuple(std::string("EnemyBullet"), entityId));
  std::cout << "bullet created" << std::endl;

  return entityId;
}