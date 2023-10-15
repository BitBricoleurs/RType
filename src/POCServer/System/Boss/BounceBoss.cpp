/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BounceBoss
*/

#include "BounceBoss.hpp"
#include <cmath>

void BounceBoss::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {

  auto bossPods = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("isBossPod"));
  auto bossCore = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("isBossCore"));

  if (bossCore == 0)
    return;
  if (!hasAppeared && !checkInScreen(bossCore, componentsContainer, eventHandler)) {
    return;
  }
  bool changedDir = false;
  auto bossVelOpt = componentsContainer.getComponent(
      bossCore,
      GameEngine::ComponentsType::getComponentType("VelocityComponent"));
  if (!bossVelOpt.has_value())
    return;
  auto bossVelComp = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
      bossVelOpt.value());

  for (auto &bossPod : bossPods) {
    auto bossPodOpt = componentsContainer.getComponent(
        bossPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
    if (!bossPodOpt.has_value())
      continue;
    auto bossPodComp = std::dynamic_pointer_cast<isBossPod>(bossPodOpt.value());

    auto podPosCompOpt = componentsContainer.getComponent(
        bossPod,
        GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!podPosCompOpt.has_value())
      continue;
    auto podPosComp =
        std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
            podPosCompOpt.value());

    auto podVelocityCompOpt = componentsContainer.getComponent(
        bossPod,
        GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    if (!podVelocityCompOpt.has_value())
      continue;
    auto podVelocityComp =
        std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
            podVelocityCompOpt.value());

    if (podPosComp->pos.x < 0 || podPosComp->pos.y < 0 ||
        podPosComp->pos.y > sizeHeight - 150 ||
        podPosComp->pos.x > sizeWidth - 150) {

      if (bossPodComp->launched) {
        auto newVelocityOpt = handleDirectionChange(podPosComp->pos, podVelocityComp->velocity);
        if (!newVelocityOpt.has_value()) {
          return;
        }
        GameEngine::Vect2 newVelocity = newVelocityOpt.value();
        podVelocityComp->velocity = newVelocity * 3;
        bossPodComp->bounces++;
      } else if (!changedDir) {
        auto newVelocityOpt = handleDirectionChange(podPosComp->pos, bossVelComp->velocity);
        if (!newVelocityOpt.has_value()) {
          return;
        }
        GameEngine::Vect2 newVelocity = newVelocityOpt.value();
        bossVelComp->velocity = newVelocity;

        for (auto &otherPod : bossPods) {
          auto otherPodOpt = componentsContainer.getComponent(otherPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
          if (!otherPodOpt.has_value())
            continue;
          auto otherPodComp =
              std::dynamic_pointer_cast<isBossPod>(otherPodOpt.value());
          if (otherPodComp->launched)
            continue;

          auto otherPodVelocityCompOpt = componentsContainer.getComponent(
              otherPod, GameEngine::ComponentsType::getComponentType(
                            "VelocityComponent"));
          if (!otherPodVelocityCompOpt.has_value())
            continue;
          auto otherPodVelocityComp =
              std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
                  otherPodVelocityCompOpt.value());

          otherPodVelocityComp->velocity.x = bossVelComp->velocity.x;
          otherPodVelocityComp->velocity.y = bossVelComp->velocity.y;
        }
        changedDir = true;
      }
    }
  }
  if (!changedDir) {
    auto posBossCoreOpt = componentsContainer.getComponent(
        bossCore,
        GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!posBossCoreOpt.has_value())
      return;
    auto posBossCoreComp =
        std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
            posBossCoreOpt.value());

    if (posBossCoreComp->pos.x < 0 || posBossCoreComp->pos.y < 0 ||
        posBossCoreComp->pos.y > sizeHeight - 150 || // boss is bouncing
        posBossCoreComp->pos.x > sizeWidth - 150) {
      auto newVelocityOpt = handleDirectionChange(posBossCoreComp->pos, bossVelComp->velocity);
      if (!newVelocityOpt.has_value()) {
        return;
      }
      GameEngine::Vect2 newVelocity = newVelocityOpt.value();
      bossVelComp->velocity = newVelocity;
    }
  }
}

bool BounceBoss::checkInScreen(
    size_t bossCore, GameEngine::ComponentsContainer &componentsContainer,
    GameEngine::EventHandler &eventHandler) {
  auto pos = componentsContainer.getComponent(
      bossCore,
      GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

  if (pos == nullptr)
    return false;
  auto posComp = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(pos.value());
  if (posComp->pos.x < 300 || posComp->pos.y < 300 ||
      posComp->pos.y > sizeHeight - 300 || posComp->pos.x > sizeWidth - 300) {
    return false;
  }
  if (!hasAppeared)
    eventHandler.scheduleEvent("launchBossPods", 200);
  hasAppeared = true;
  return true;
}

float BounceBoss::randomizeVelocity(float currentVelocity) {
  float randomizedValue =
      1.0f + static_cast<float>(rand()) /
                 (static_cast<float>(RAND_MAX) / 2.0f);

  float direction = (currentVelocity >= 0) ? 1.0f : -1.0f;

  return randomizedValue * direction;
}

std::optional<GameEngine::Vect2>
BounceBoss::handleDirectionChange(GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {
  bool touchesLeft = pos.x < 0;
  bool touchesRight = pos.x > sizeWidth - 150;
  bool touchesTop = pos.y < 0;
  bool touchesBottom = pos.y > sizeHeight - 150;

  if ((touchesLeft && velocity.x > 0) || (touchesRight && velocity.x < 0) ||
      (touchesTop && velocity.y > 0) || (touchesBottom && velocity.y < 0)) {
    return std::nullopt;
  }

  velocity.x = randomizeVelocity(velocity.x);
  velocity.y = randomizeVelocity(velocity.y);

  if (touchesLeft || touchesRight) {
    velocity.x = -velocity.x;
  }
  if (touchesTop || touchesBottom) {
    velocity.y = -velocity.y;
  }

  return velocity;
}
