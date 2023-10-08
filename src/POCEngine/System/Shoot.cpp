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

void Shoot::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto event = eventHandler.getTriggeredEvent().second;
    auto entityID = std::any_cast<size_t>(event);
    auto player = componentsContainer.getComponentsFromEntity(entityID);
    auto positionOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    auto shooterOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("Shooter"));
    if (positionOptional.has_value() && shooterOptional.has_value()) {
        auto posComp = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOptional.value());
        auto shooterComp = std::dynamic_pointer_cast<Shooter>(shooterOptional.value());

        GameEngine::Vect2 shootingPosition(posComp->pos.x + shooterComp->shootPosition.x, posComp->pos.y + shooterComp->shootPosition.y);
        float rotation = 0.0f;
        float scale = 0.0f;
        GameEngine::ColorR tint = {255, 255, 255, 255};
        GameEngine::rect rect1;
        std::string spritePath;
        GameEngine::Vect2 velocity = GameEngine::Vect2(0,0);

        auto bullet = componentsContainer.createEntity();
        if (shooterComp->typeBullet == 0) {
            auto chargeAnimations = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("ChargeShoot"));
            for (auto &chargeId : chargeAnimations) {
                auto chargeOpt = componentsContainer.getComponent(chargeId, GameEngine::ComponentsType::getComponentType("ChargeShoot"));
                if (chargeOpt.has_value()) {
                    auto charge = std::dynamic_pointer_cast<ChargeShoot>(chargeOpt.value());
                    if (charge->charge > 50) {
                        charge->charge = 0;
                        rect1 = GameEngine::rect(0, 0, 80, 16);
                        scale = 2.5f;
                        spritePath = "assets/ShootCharge.gif";
                        velocity.x = 15;
                        shootingPosition.y = shootingPosition.y - 15;
                    } else {
                        rect1 = GameEngine::rect(0, 0, 16, 4);
                        scale = 2.5f;
                        spritePath = "assets/shoot.gif";
                        velocity.x = 20;
                    }
                }
            }
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
        auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(spritePath, shootingPosition, rect1, 10, scale, rotation, tint);
        auto AABBComponent = std::make_shared<GameEngine::AABBComponent2D>(GameEngine::Vect2(shootingPosition.x, shootingPosition.y), GameEngine::Vect2(shootingPosition.x + rect1.w, shootingPosition.y + rect1.h));
        auto rectangleCollider = std::make_shared<GameEngine::RectangleColliderComponent2D>(rect1);
        auto PositionComponent = std::make_shared<GameEngine::PositionComponent2D>(GameEngine::Vect2(shootingPosition.x, shootingPosition.y));
        auto isBulletComponent = std::make_shared<IsBullet>();
        auto velocityComponent = std::make_shared<GameEngine::VelocityComponent>(velocity);
        auto movementComponent = std::make_shared<GameEngine::MovementComponent>();
        componentsContainer.bindComponentToEntity(bullet, spriteComponent);
        componentsContainer.bindComponentToEntity(bullet, rectangleCollider);
        componentsContainer.bindComponentToEntity(bullet, AABBComponent);
        componentsContainer.bindComponentToEntity(bullet, velocityComponent);
        componentsContainer.bindComponentToEntity(bullet, movementComponent);
        componentsContainer.bindComponentToEntity(bullet, PositionComponent);
        componentsContainer.bindComponentToEntity(bullet, isBulletComponent);
    }
  }
}
