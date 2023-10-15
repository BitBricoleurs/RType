/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateBoss
*/

#include "EntityFactory.hpp"
#include <cstddef>

size_t
EntityFactory::createBellmiteBoss(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {
  size_t entityId = createBossMob(container, "assets/bellmite-core.png", 64, 64,
                                  1, false, false, "assets/explode-mob.gif", 33,
                                  200, 6, pos, velocity, 100, 10, 1, 2.0f);
  return entityId;
}

size_t
EntityFactory::createBellmitePod(GameEngine::ComponentsContainer &container,
                                 GameEngine::EventHandler &eventHandler,
                                 GameEngine::Vect2 pos,
                                 GameEngine::Vect2 velocity) {
  size_t entityId = createBossMob(
      container, "assets/bellmite-entities.png", 29, 124, 4, false, false,
      "assets/explode-mob.gif", 33, 200, 6, pos, velocity, 100, 10, 1, 4.0f);
  eventHandler.scheduleEvent("animate", 8,
                             std::make_tuple(std::string("Pods"), entityId));
  return entityId;
}

// const float PI = 3.14159265358979323846;
const int totalPods = 30;
// const float PI = 3.14159265358979323846;
const float podDiameter = 64.0 * 3;               // 64px scaled by 4
const float maxRadius = 400.0 / 2;                // Half of the total diameter
const float radiusIncrement = podDiameter * 0.75; // Overlap by 25%

size_t EntityFactory::createBellmite(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos,
                                     GameEngine::Vect2 velocity) {

  float currentRadius = 0;
  int podsInCurrentRadius = 1;

  for (int i = 0; i < totalPods;) {
    float angleIncrement = 2 * PI / podsInCurrentRadius;

    for (int j = 0; j < podsInCurrentRadius && i < totalPods; j++, i++) {
      GameEngine::Vect2 podPos;
      podPos.x = pos.x + currentRadius * cos(j * angleIncrement);
      podPos.y = pos.y + currentRadius * sin(j * angleIncrement);

      createBellmitePod(container, eventHandler, podPos, velocity);
    }

    currentRadius += radiusIncrement;
    podsInCurrentRadius += 6; // Approximate increase, adjust accordingly
  }

  return 0;
}
