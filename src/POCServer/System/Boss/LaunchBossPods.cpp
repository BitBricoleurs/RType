/*
** EPITECH PROJECT, 2023
** RType
** File description:
** LaunchBossPods
*/

#include "LaunchBossPods.hpp"
#include <algorithm>
#include <iostream>
#include <random>

void LaunchBossPods::update(
    GameEngine::ComponentsContainer &componentsContainer,
    GameEngine::EventHandler &eventHandler) {

  auto bossPods = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("isBossPod"));

  size_t podToLaunch = 0;

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(bossPods.begin(), bossPods.end(), g);

  for (auto &bossPod : bossPods) {
    auto bossPodOpt = componentsContainer.getComponent(
        bossPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
    if (!bossPodOpt.has_value())
      continue;
    auto bossPodComp = std::dynamic_pointer_cast<isBossPod>(bossPodOpt.value());
    if (bossPodComp->launched == true)
      continue;
    bossPodComp->launched = true;
    podToLaunch = bossPod;
    break;
  }
  if (podToLaunch == 0)
    return;
  auto podPositionOpt = componentsContainer.getComponent(
      podToLaunch,
      GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
  if (!podPositionOpt.has_value())
    return;
  auto podPositionComp =
      std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
          podPositionOpt.value());

  auto players = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
  GameEngine::Vect2 velocity;
  float closestDistance = std::numeric_limits<float>::max();
  GameEngine::Vect2 directionToClosestPlayer;
  for (auto &player : players) {
    auto positionOpt = componentsContainer.getComponent(
        player,
        GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    auto positionComp =
        std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
            positionOpt.value());
    if (positionComp) {
      GameEngine::Vect2 directionToPlayer =
          positionComp->pos - podPositionComp->pos;
      float distanceToPlayer = directionToPlayer.magnitude();
      if (distanceToPlayer < closestDistance) {
        closestDistance = distanceToPlayer;
        directionToClosestPlayer = directionToPlayer;
      }
    }
  }
  auto velocityOpt = componentsContainer.getComponent(
      podToLaunch,
      GameEngine::ComponentsType::getComponentType("VelocityComponent"));
  if (!velocityOpt.has_value())
    return;
  auto velocityComp = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
      velocityOpt.value());
  if (closestDistance < std::numeric_limits<float>::max()) {
    float maxVal = std::max(std::abs(directionToClosestPlayer.x),
                            std::abs(directionToClosestPlayer.y));
    float scaleFactor = 9.0f / maxVal;
    velocity = directionToClosestPlayer * scaleFactor;
    velocityComp->velocity = velocity;
  }
}
