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
                                  GameEngine::Vect2 velocity, const std::string &path, GameEngine::rect rect1) {
  size_t entityId = createBullet(container, path, rect1.h, rect1.w, 1, false,
                                 false, pos, velocity, 50, true, 2.5);

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