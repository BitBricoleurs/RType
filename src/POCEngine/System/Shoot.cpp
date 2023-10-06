//
// Created by alexandre on 03/10/23.
//

#include "Shoot.hpp"
#include "MovementComponent2D.hpp"
#include "Shooter.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include <cmath>
void Shoot::update(GameEngine::ComponentsContainer &componentsContainer,
                   GameEngine::EventHandler &eventHandler) {

  auto event = eventHandler.getTriggeredEvent().second;
  auto entityID = std::any_cast<size_t>(event);

  auto spriteOptional = componentsContainer.getComponent(
      entityID,
      GameEngine::ComponentsType::getComponentType("SpriteComponent"));
  auto shooterOptional = componentsContainer.getComponent(
      entityID, GameEngine::ComponentsType::getComponentType("Shooter"));

  if (spriteOptional.has_value() && shooterOptional.has_value()) {
    auto spriteComp = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(
        spriteOptional.value());
    auto shooterComp =
        std::dynamic_pointer_cast<Shooter>(shooterOptional.value());

    GameEngine::Vect2 shootingPosition(
        spriteComp->pos.x + shooterComp->shootPosition.x,
        spriteComp->pos.y + shooterComp->shootPosition.y);

    if (shooterComp->typeBullet == 0) {
      EntityFactory::getInstance().createPlayerBullet(
          componentsContainer, eventHandler, shootingPosition,
          shooterComp->velocity);
    } else if (shooterComp->typeBullet == 1) {
      std::cout << "Entity " << entityID << " shooting" << std::endl;
      auto players = componentsContainer.getEntitiesWithComponent(
          GameEngine::ComponentsType::getComponentType("IsPlayer"));
      GameEngine::Vect2 velocity;
      float closestDistance = std::numeric_limits<float>::max();

      GameEngine::Vect2 directionToClosestPlayer;

      for (auto &player : players) {
        auto positionOpt = componentsContainer.getComponent(
            player, GameEngine::ComponentsType::getComponentType(
                        "PositionComponent2D"));
        auto positionComp =
            std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
                positionOpt.value());

        if (positionComp) {
          std::cout << "player pos: " << positionComp->pos.x << ", "
                    << positionComp->pos.y << std::endl;
          GameEngine::Vect2 directionToPlayer =
              positionComp->pos - shootingPosition;
          float distanceToPlayer = directionToPlayer.magnitude();

          if (distanceToPlayer < closestDistance) {
            closestDistance = distanceToPlayer;
            directionToClosestPlayer = directionToPlayer;
          }
        }
      }

      std::cout << "Direction to Player: (" << directionToClosestPlayer.x
                << ", " << directionToClosestPlayer.y << ")\n";

      if (closestDistance < std::numeric_limits<float>::max()) {
        float maxVal = std::max(std::abs(directionToClosestPlayer.x),
                                std::abs(directionToClosestPlayer.y));
        float scaleFactor = 6.0f / maxVal;
        velocity = directionToClosestPlayer * scaleFactor;
        EntityFactory::getInstance().createBaseEnemyBullet(
            componentsContainer, eventHandler, shootingPosition, velocity);
      }
    }
  }
}
