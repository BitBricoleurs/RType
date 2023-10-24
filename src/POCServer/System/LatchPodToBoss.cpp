/*
** EPITECH PROJECT, 2023
** RType
** File description:
** LatchPodToBoss
*/

#include "LatchPodToBoss.hpp"
#include <cstddef>

namespace Server {
void LatchPodToBoss::update(
    GameEngine::ComponentsContainer &componentsContainer,
    GameEngine::EventHandler &eventHandler) {
  auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(
      eventHandler.getTriggeredEvent().second);
  auto firstEntityOptBossCore = componentsContainer.getComponent(
      firstEntity, GameEngine::ComponentsType::getComponentType("isBossCore"));
  size_t bossCore = 0;
  size_t bossPod = 0;
  if (firstEntityOptBossCore.has_value()) {
    bossCore = firstEntity;
    bossPod = secondEntity;
  } else {
    bossCore = secondEntity;
    bossPod = firstEntity;
  }
  auto bossCoreVelOpt = componentsContainer.getComponent(
      bossCore,
      GameEngine::ComponentsType::getComponentType("VelocityComponent"));
  if (!bossCoreVelOpt.has_value())
    return;
  auto bossCoreVelComp =
      std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(
          bossCoreVelOpt.value());

  auto bossPodVelOpt = componentsContainer.getComponent(
      bossPod,
      GameEngine::ComponentsType::getComponentType("VelocityComponent"));
  if (!bossPodVelOpt.has_value())
    return;
  auto bossPodVelComp =
      std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(
          bossPodVelOpt.value());

  bossPodVelComp->velocity.x = bossCoreVelComp->velocity.x;
  bossPodVelComp->velocity.y = bossCoreVelComp->velocity.y;

  auto bossPodOpt = componentsContainer.getComponent(
      bossPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
  if (!bossPodOpt.has_value())
    return;
  auto bossPodComp = std::dynamic_pointer_cast<isBossPod>(bossPodOpt.value());
  bossPodComp->launched = false;
  bossPodComp->bounces = 0;
  std::cout << "latched pod: " << secondEntity << std::endl;
}
} // namespace Server