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

  size_t entityId = createBaseMob(container, "assets/cancerMob.gif", 34, 200, 6,
                                  true, true, "assets/explosion.gif", 33, 200,
                                  6, pos, velocity, 100, 10, 2.5f);
  auto shooterComp = std::make_shared<Shooter>(GameEngine::Vect2(0, 50),1);
  container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
  container.bindComponentToEntity(entityId, shooterComp);
  eventHandler.scheduleEvent("animate", 30,
                             std::make_tuple(std::string("Cancer"), entityId));
  auto IdCharge = std::make_tuple(entityId, 0);
  eventHandler.scheduleEvent("ShootSystem", 300, IdCharge);
  return entityId;
}

size_t
EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                GameEngine::EventHandler &eventHandler,
                                GameEngine::Vect2 pos,
                                GameEngine::Vect2 velocity) {
  size_t entityId = createBaseMob(
      container, "assets/patapataMob2.gif", 24, 523, 16, true,
      false, "assets/explosion.gif", 33, 200, 6, pos, velocity, 100, 10, 2.5f);

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
                                  6, pos, velocity, 100, 10, 2.5f);

  container.bindComponentToEntity(entityId, std::make_shared<Bug>());
  return entityId;
}
