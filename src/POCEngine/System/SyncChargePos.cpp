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
      if (strcmp(triggeredEvent.c_str(), "SPACE_KEY_PRESSED")) {
        position->pos.x = -100;
        position->pos.y = -100;
        return;
      }

      auto charge = std::dynamic_pointer_cast<ChargeShoot>(chargeOpt.value());
      auto playerPosOpt = componentsContainer.getComponent(
          charge->player,
          GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
      if (playerPosOpt.has_value()) {
        auto playerPos =
            std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
                playerPosOpt.value());
        position->pos.y = playerPos->pos.y - 10;
        position->pos.x = playerPos->pos.x + 80;
        std::cout << position->pos.x << ", " << position->pos.x << " | "
                  << playerPos->pos.y << ", " << playerPos->pos.y << std::endl;
      }
    }
  }
}
