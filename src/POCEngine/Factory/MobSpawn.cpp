/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobSpawn
*/

#include "EntityFactory.hpp"

size_t EntityFactory::spawnCancerMob(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos,
                                     GameEngine::Vect2 velocity) {

  size_t entityId =
      createBaseMob(container, "assets/cancerMob.gif", 34, 200, 6, true, true,
                    "assets/explosion.gif", 33, 200, 6, pos, velocity, 32, 32,
                    100, 10, 0, 0, 2.5f);
  container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
  eventHandler.scheduleEvent("animate", 30,
                             std::make_tuple(std::string("Cancer"), entityId));
  return entityId;
}

size_t
EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                GameEngine::EventHandler &eventHandler,
                                GameEngine::Vect2 pos,
                                GameEngine::Vect2 velocity) {
  size_t entityId =
      createBaseMob(container, "assets/epitech_assets/pataPataMob.gif", 36, 533,
                    16, true, false, "assets/explosion.gif", 33, 200, 6, pos,
                    velocity, 36, 36, 100, 10, 0, 0, 2.5f);

  container.bindComponentToEntity(entityId, std::make_shared<PataPata>());
  container.bindComponentToEntity(
      entityId, std::make_shared<HeightVariation>(3, 75, pos.y));

  eventHandler.scheduleEvent(
      "animate", 10, std::make_tuple(std::string("PataPata"), entityId));
  return entityId;
}

size_t EntityFactory::spawnBugMob(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {

  size_t entityId = createBaseMob(container, "assets/bugMob.png", 34, 532, 16,
                                  false, false, "assets/explosion.gif", 33, 200,
                                  6, pos, velocity, 32, 32, 100, 10, 0, 0);

  container.bindComponentToEntity(entityId, std::make_shared<Bug>());
  return entityId;
}
