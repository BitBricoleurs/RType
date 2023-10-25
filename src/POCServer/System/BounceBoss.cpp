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

  // check if boss exists and is in scope
  if (bossCore == 0)
    return;
  if (!hasAppeared &&
      !checkInScreen(bossCore, componentsContainer, eventHandler)) {
    return;
  }
  bool changedDir = false;

  auto bossVelOpt = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
  auto bossPosOpt = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

  if (!bossVelOpt.has_value() || !bossPosOpt.has_value())
    return;

  auto bossVelComp = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(bossVelOpt.value());
  auto bossPosComp = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(bossPosOpt.value());

  // check if boss pods is bouncing on the screen
  for (auto &bossPod : bossPods) {
      auto bossPodOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
      auto podPosCompOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
      auto podVelocityCompOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));

      if (!bossPodOpt.has_value() || !podPosCompOpt.has_value() || !podVelocityCompOpt.has_value())
          continue;

    auto bossPodComp = std::dynamic_pointer_cast<isBossPod>(bossPodOpt.value());
    auto podPosComp = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(podPosCompOpt.value());
    auto podVelocityComp = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(podVelocityCompOpt.value());


    if (bossPodComp->launched ) {
       std::cout << "pod: " << bossPod << " is launched" << std::endl;
       std::cout << "pod: " << bossPod << " pos " << podPosComp->pos.x << " " << podPosComp->pos.y << std::endl;
       std::cout << "pod: " << bossPod << " vel " << podVelocityComp->velocity.x << " " << podVelocityComp->velocity.y << std::endl;
    }


    if (podPosComp->pos.x < 0 || podPosComp->pos.y < 0 ||
        podPosComp->pos.y > 1080 - 150 || // one of the pods is bouncing
        podPosComp->pos.x > 1920 - 150) {

        std::cout << "detected bounce" << std::endl;
        std::cout << "pod " << bossPod << " pos " << podPosComp->pos.x << " " << podPosComp->pos.y << std::endl;
        std::cout << "pod " << bossPod << " vel " << podVelocityComp->velocity.x << " " << podVelocityComp->velocity.y << std::endl;
        std::cout << "launched: " << bossPodComp->launched << std::endl;

      if (bossPodComp->launched) { // if pod is detached from the core
          std::cout << "pod: " << bossPod << " is detached" << std::endl;
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
        factory.updateEntityNetwork(eventHandler, bossPod, podPosComp->pos,
                                    podVelocityComp->velocity);
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
        factory.updateEntityNetwork(eventHandler, bossCore, bossPosComp->pos,
                                           bossVelComp->velocity);
        for (auto &otherPod : bossPods) {

          auto otherPodOpt = componentsContainer.getComponent(otherPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
          auto otherPodVelocityCompOpt = componentsContainer.getComponent(otherPod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
          auto otherPodPosOpt = componentsContainer.getComponent(otherPod, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
          if (!otherPodOpt.has_value() || !otherPodVelocityCompOpt.has_value() || !otherPodPosOpt.has_value()) // check if the pod is detached from the core, and don't apply velocity if its detached
            continue;
          auto otherPodComp = std::dynamic_pointer_cast<isBossPod>(otherPodOpt.value());

          if (otherPodComp->launched)
            continue;

          auto otherPodVelocityComp = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(otherPodVelocityCompOpt.value());
          auto otherPodPosComp = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(otherPodPosOpt.value());

          otherPodVelocityComp->velocity.x = bossVelComp->velocity.x;
          otherPodVelocityComp->velocity.y = bossVelComp->velocity.y;
          factory.updateEntityNetwork(eventHandler, otherPod, otherPodPosComp->pos,
                                      otherPodVelocityComp->velocity);
        }
        changedDir = true;
      }
    }
  }
  // the boss has no more pods attached, check if boss is bouncing
  if (!changedDir) {
    auto posBossCoreOpt = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!posBossCoreOpt.has_value())
      return;
    auto posBossCoreComp = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(posBossCoreOpt.value());

    if (posBossCoreComp->pos.x < 0 || posBossCoreComp->pos.y < 0 ||
        posBossCoreComp->pos.y > 1080 - 150 || // boss is bouncing
        posBossCoreComp->pos.x > 1920 - 150) {

      auto newVelocityOpt = handleDirectionChange(
              posBossCoreComp->pos,
              bossVelComp->velocity);    // core, and set all the pods
      if (!newVelocityOpt.has_value()) { // velocity to be the same
        return;
      }
      Utils::Vect2 newVelocity = newVelocityOpt.value();
      bossVelComp->velocity = newVelocity;
        factory.updateEntityNetwork(eventHandler, bossCore, posBossCoreComp->pos,
                                    bossVelComp->velocity);
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
  auto posComp = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(
      pos.value());
  if (posComp->pos.x < 300 || posComp->pos.y < 300 ||
      posComp->pos.y > 1080 - 300 || posComp->pos.x > 1920 - 300) {
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