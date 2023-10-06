/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SyncChargePos
*/

#include "SyncChargePos.hpp"

void SyncChargePos::update(GameEngine::ComponentsContainer &componentsContainer,
                           GameEngine::EventHandler &eventHandler) {
  auto triggeredEvent = eventHandler.getTriggeredEvent().first;

  std::cout << triggeredEvent << std::endl;
  auto chargeAnimations = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("ChargeShoot"));

  for (auto &chargeId : chargeAnimations) {

    auto chargeOpt = componentsContainer.getComponent(
        chargeId, GameEngine::ComponentsType::getComponentType("ChargeShoot"));
    auto positionOpt = componentsContainer.getComponent(
        chargeId,
        GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

    if (chargeOpt.has_value() && positionOpt.has_value()) {
      auto position =
          std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
              positionOpt.value());
      auto charge = std::dynamic_pointer_cast<ChargeShoot>(chargeOpt.value());
      if (strcmp(triggeredEvent.c_str(), "SPACE_KEY_RELEASED") == 0) {
        std::cout << "released" << std::endl;
        position->pos.x = -100;
        position->pos.y = -100;
        std::cout << position->pos.x << ", " << position->pos.y << std::endl;
        return;
      } else if (strcmp(triggeredEvent.c_str(), "STOP_UNCHARGING") == 0) {
        std::cout << "stopped" << std::endl;
        eventHandler.scheduleEvent("ShootSystem", 20, charge->player);
        return;
      } else
        std::cout << "pressed" << std::endl;
      eventHandler.unscheduleEvent("ShootSystem");

      auto playerPosOpt = componentsContainer.getComponent(
          charge->player,
          GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
      if (playerPosOpt.has_value()) {
        auto playerPos =
            std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
                playerPosOpt.value());
        position->pos.y = playerPos->pos.y - 10;
        position->pos.x = playerPos->pos.x + 80;
      }
    }
  }
}
