/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateBoss
*/

#include "EntityFactory.hpp"
#include "BossComponent.hpp"
#include <cmath>
#include <cstddef>

size_t
EntityFactory::createBellmiteBoss(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {
  size_t entityId = createBossMob(container, "assets/bellmite-core.png", 64, 64,
                                  1, false, false, "assets/boss-explode.png",
                                  64, 320, 5, pos, velocity, 0, 2.0f, 0, GameEngine::ColorR(255, 255, 255, 255), 7);
  auto bossCore = std::make_shared<isBossCore>();
  container.bindComponentToEntity(entityId, bossCore);
  container.unbindComponentFromEntity(
      entityId, GameEngine::ComponentsType::getComponentType("Health"));
  return entityId;
}

size_t
EntityFactory::createBellmitePod(GameEngine::ComponentsContainer &container,
                                 GameEngine::EventHandler &eventHandler,
                                 GameEngine::Vect2 pos,
                                 GameEngine::Vect2 velocity) {
  size_t entityId = createBossMob(
      container, "assets/bellmite-entities.png", 29, 124, 4, false, false,
      "assets/explode-mob.gif", 33, 200, 6, pos, velocity, 0, 3.0f, 0.0f, GameEngine::ColorR(255, 255, 255, 255), 7);
  auto bossPod = std::make_shared<isBossPod>();
  container.bindComponentToEntity(entityId, bossPod);
  eventHandler.scheduleEvent("animate", 8,
                             std::make_tuple(std::string("Pods"), entityId));
  return entityId;
}

