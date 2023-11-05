/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BounceBoss
*/

#include "BounceBoss.hpp"
#include <cmath>

namespace Server {

void BounceBoss::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {

  auto bossPods = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("isBossPod"));
  auto bossCore = componentsContainer.getEntityWithUniqueComponent(
      GameEngine::ComponentsType::getComponentType("isBossCore"));

  auto &factory = EntityFactory::getInstance();

  bool changedDir = false;
  auto bossVelOpt = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
  auto bossPosOpt = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

  if (!bossVelOpt.has_value() || !bossPosOpt.has_value())
    return;

  auto bossVelComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(bossVelOpt.value());
  auto bossPosComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(bossPosOpt.value());
  int i = 0;
  // check if boss pods is bouncing on the screen
  for (auto &bossPod : bossPods) {
      auto bossPodOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
      auto podPosCompOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
      auto podVelocityCompOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));

      if (!bossPodOpt.has_value() || !podPosCompOpt.has_value() || !podVelocityCompOpt.has_value())
          continue;

    auto bossPodComp = std::static_pointer_cast<isBossPod>(bossPodOpt.value());
    auto podPosComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(podPosCompOpt.value());
    auto podVelocityComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(podVelocityCompOpt.value());

    if (podPosComp->pos.x < 0 || podPosComp->pos.y < 0 ||
        podPosComp->pos.y > 1080 - 150 || // one of the pods is bouncing
        podPosComp->pos.x > 1920 - 150) {

      if (bossPodComp->launched) { // if pod is detached from the core
        auto newVelocityOpt =      // change only its velocity
            handleDirectionChange(
                podPosComp->pos,
                podVelocityComp->velocity); // change velocity of the boss's
        if (!newVelocityOpt.has_value()) {
          return;
        }
        Utils::Vect2 newVelocity = newVelocityOpt.value();
        podVelocityComp->velocity = newVelocity * 3;
        bossPodComp->bounces++;
        factory.updateEntityNetworkWithVelocity(eventHandler, bossPod, podVelocityComp->velocity);
      } else if (!changedDir) {

        auto newVelocityOpt = // change velocity of the boss's
            handleDirectionChange(
                podPosComp->pos,
                bossVelComp->velocity);    // core, and set all the pods
        if (!newVelocityOpt.has_value()) { // velocity to be the same
          return;
        }
        Utils::Vect2 newVelocity = newVelocityOpt.value();
        bossVelComp->velocity = newVelocity;
        factory.updateEntityNetworkWithVelocity(eventHandler, bossCore,
                                           bossVelComp->velocity);
        for (auto &otherPod : bossPods) {

          auto otherPodOpt = componentsContainer.getComponent(otherPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
          auto otherPodVelocityCompOpt = componentsContainer.getComponent(otherPod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
          auto otherPodPosOpt = componentsContainer.getComponent(otherPod, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
          if (!otherPodOpt.has_value() || !otherPodVelocityCompOpt.has_value() || !otherPodPosOpt.has_value()) // check if the pod is detached from the core, and don't apply velocity if its detached
            continue;
          auto otherPodComp = std::static_pointer_cast<isBossPod>(otherPodOpt.value());

          if (otherPodComp->launched)
            continue;

          auto otherPodVelocityComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(otherPodVelocityCompOpt.value());
          auto otherPodPosComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(otherPodPosOpt.value());

          otherPodVelocityComp->velocity.x = bossVelComp->velocity.x;
          otherPodVelocityComp->velocity.y = bossVelComp->velocity.y;
          factory.updateEntityNetworkWithVelocity(eventHandler, otherPod,
                                      otherPodVelocityComp->velocity);
        }
        changedDir = true;
        return;
      }
    }
  }
  // the boss has no more pods attached, check if boss is bouncing
  if (!changedDir) {
    if (bossPosComp->pos.x < 0 || bossPosComp->pos.y < 0 ||
        bossPosComp->pos.y > 1080 - 150 || // boss is bouncing
        bossPosComp->pos.x > 1920 - 150) {

      auto newVelocityOpt = handleDirectionChange(
              bossPosComp->pos,
              bossVelComp->velocity);    // core, and set all the pods
      if (!newVelocityOpt.has_value()) { // velocity to be the same
        return;
      }
      Utils::Vect2 newVelocity = newVelocityOpt.value();
      bossVelComp->velocity = newVelocity;
        factory.updateEntityNetworkWithVelocity(eventHandler, bossCore,
                                    bossVelComp->velocity);
    }
  }
}

float BounceBoss::randomizeVelocity(float currentVelocity) {
  float randomizedValue =
      1.0f + static_cast<float>(rand()) /
                 (static_cast<float>(RAND_MAX) / 2.0f); // Between 1 and 3

  float direction = (currentVelocity >= 0) ? 1.0f : -1.0f;

  return randomizedValue * direction;
}

std::optional<Utils::Vect2>
BounceBoss::handleDirectionChange(Utils::Vect2 pos, Utils::Vect2 velocity) {
  bool touchesLeft = pos.x < 0;
  bool touchesRight = pos.x > 1920 - 150;
  bool touchesTop = pos.y < 0;
  bool touchesBottom = pos.y > 1080 - 150;

  if ((touchesLeft && velocity.x > 0) || (touchesRight && velocity.x < 0) ||
      (touchesTop && velocity.y > 0) || (touchesBottom && velocity.y < 0)) {
    return std::nullopt; // Indicates that no changes should be made
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

} // namespace Server