//
// Created by alexandre on 03/10/23.
//

#include "Shoot.hpp"
#include "MovementComponent2D.hpp"
#include "Shooter.hpp"
#include "Utils.hpp"
#include "IsBullet.hpp"
#include "VelocityComponent.hpp"
#include <cmath>
void Shoot::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto charge = 0;
    auto event = eventHandler.getTriggeredEvent().second;
   auto tupleIdCharge = std::any_cast<std::tuple<unsigned long, int>>(event);
    size_t entityID = std::get<0>(tupleIdCharge);
    charge = std::get<1>(tupleIdCharge);
    auto player = componentsContainer.getComponentsFromEntity(entityID);
    auto positionOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    auto shooterOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("Shooter"));
    if (positionOptional.has_value() && shooterOptional.has_value()) {
        auto posComp = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOptional.value());
        auto shooterComp = std::dynamic_pointer_cast<Shooter>(shooterOptional.value());

        GameEngine::Vect2 shootingPosition(posComp->pos.x + shooterComp->shootPosition.x, posComp->pos.y + shooterComp->shootPosition.y);
        if (shooterComp->typeBullet == 0) {
            if (charge > 50) {
                shootingPosition.y = shootingPosition.y - 15;
                EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, shootingPosition, GameEngine::Vect2(15,0), "assets/ShootCharge.gif", GameEngine::rect(0, 0, 80, 16));
            } else {
                EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, shootingPosition, GameEngine::Vect2(20,0), "assets/shoot.gif", GameEngine::rect(0, 0, 16, 4));
            }
        } else if (shooterComp->typeBullet == 1) {
            auto players = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
            GameEngine::Vect2 velocity;
            float closestDistance = std::numeric_limits<float>::max();
            GameEngine::Vect2 directionToClosestPlayer;
            for (auto &player : players) {
                auto positionOpt = componentsContainer.getComponent(player, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                auto positionComp = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOpt.value());
                if (positionComp) {
                    GameEngine::Vect2 directionToPlayer = positionComp->pos - shootingPosition;
                    float distanceToPlayer = directionToPlayer.magnitude();
                    if (distanceToPlayer < closestDistance) {
                        closestDistance = distanceToPlayer;
                        directionToClosestPlayer = directionToPlayer;
                    }
                }
            }
            if (closestDistance < std::numeric_limits<float>::max()) {
              float maxVal = std::max(std::abs(directionToClosestPlayer.x), std::abs(directionToClosestPlayer.y));
              float scaleFactor = 6.0f / maxVal;
              velocity = directionToClosestPlayer * scaleFactor;
              EntityFactory::getInstance().createBaseEnemyBullet(componentsContainer, eventHandler, shootingPosition, velocity);
      }
        }
    }
}
