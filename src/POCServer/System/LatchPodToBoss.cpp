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
      try {
          std::cout << "latch to boss" << std::endl;
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
      auto &factory = EntityFactory::getInstance();
      auto bossCoreVelOpt = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
      auto bossCorePosOpt = componentsContainer.getComponent(bossCore, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
      auto bossPodVelOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
      auto bossPodPosOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
      auto bossPodOpt = componentsContainer.getComponent(bossPod, GameEngine::ComponentsType::getComponentType("isBossPod"));
      if (!bossCoreVelOpt.has_value() || !bossPodVelOpt.has_value() || !bossPodOpt.has_value() || !bossCorePosOpt.has_value() || !bossPodPosOpt.has_value())
        return;
      auto bossCoreVelComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(bossCoreVelOpt.value());
      auto bossCorePosComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(bossCorePosOpt.value());
      auto bossPodVelComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(bossPodVelOpt.value());
      auto bossPodPosComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(bossPodPosOpt.value());
      auto bossPodComp = std::static_pointer_cast<isBossPod>(bossPodOpt.value());

      bossPodVelComp->velocity.x = bossCoreVelComp->velocity.x;
      bossPodVelComp->velocity.y = bossCoreVelComp->velocity.y;

      bossPodComp->launched = false;
      bossPodComp->bounces = 0;
      std::cout << "latched pod: " << secondEntity << std::endl;
      factory.updateEntityNetwork(eventHandler, bossPod, bossPodPosComp->pos, bossPodVelComp->velocity);
      factory.updateEntityNetwork(eventHandler, bossCore, bossCorePosComp->pos, bossCoreVelComp->velocity);
    } catch (const std::bad_any_cast&) {
        std::cerr << "Cast error in LatchPodToBoss::update" << std::endl;
    }
}
} // namespace Server