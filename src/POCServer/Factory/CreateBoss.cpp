/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateBoss
*/

#include "EntityFactory.hpp"
#include <cstddef>
#include <cmath>

size_t
EntityFactory::createBellmiteBoss(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {
  size_t entityId = createBossMob(container, 64, 64, pos, velocity, 100, 10, 1, 2.0f);
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
      container, 29, 31, pos, velocity, 100, 50, 1, 3.0f);
  auto bossPod = std::make_shared<isBossPod>();
  container.bindComponentToEntity(entityId, bossPod);
  eventHandler.scheduleEvent("animate", 8,
                             std::make_tuple(std::string("Pods"), entityId));
  return entityId;
}

size_t EntityFactory::createBellmite(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos,
                                     bool dropPowerup) {

  const int totalPods = 21;
  const float podDiameter = 64.0 * 1.5f;
  const float maxRadius = 800.0 / 2;
  const float radiusIncrement = podDiameter * 0.80;

  GameEngine::Vect2 velocity = GameEngine::Vect2(0, 0);
  createBellmiteBoss(container, eventHandler, pos, velocity);

  float currentRadius = 0;
  int podsInCurrentRadius = 1;

  for (int i = 0; i < totalPods;) {
    float angleIncrement = 2 * M_PI / podsInCurrentRadius;

    for (int j = 0; j < podsInCurrentRadius && i < totalPods; j++, i++) {
      GameEngine::Vect2 podPos;
      podPos.x = pos.x + currentRadius * cos(j * angleIncrement);
      podPos.y = pos.y + currentRadius * sin(j * angleIncrement);

      createBellmitePod(container, eventHandler, podPos, velocity);
    }

    currentRadius += radiusIncrement;
    podsInCurrentRadius += 6;
  }

  eventHandler.scheduleEvent("bounceBoss", 2);

  return 0;
}
