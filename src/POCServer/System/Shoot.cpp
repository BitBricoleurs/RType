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

void Shoot::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{

   auto tupleIdCharge = std::any_cast<std::tuple<unsigned long, int>>(eventHandler.getTriggeredEvent().second);
   size_t entityID = std::get<0>(tupleIdCharge);
   auto charge = std::get<1>(tupleIdCharge);



   auto entityComp = componentsContainer.getComponentsFromEntity(entityID);

   auto posType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
   auto shooterType = GameEngine::ComponentsType::getComponentType("Shooter");

   auto positionOptional = componentsContainer.getComponent(entityID, posType);
   auto shooterOptional = componentsContainer.getComponent(entityID, shooterType);

    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::IMessage> messageOut;
    std::shared_ptr<Network::AllUsersMessage> userMessage;
    BulletType bulletType;
    BulletOwner bulletOwner;

   size_t bullet = 0;
   if (positionOptional.has_value() && shooterOptional.has_value()) {
        auto posComp = std::static_pointer_cast<GameEngine::PositionComponent2D>(positionOptional.value());
        auto shooterComp = std::static_pointer_cast<Shooter>(shooterOptional.value());

        GameEngine::Vect2 shootingPosition(posComp->pos.x + shooterComp->shootPosition.x, posComp->pos.y + shooterComp->shootPosition.y);
        if (shooterComp->typeBullet == BulletTypeEntity::PlayerBullet) {
            if (charge >= 50) {
                shootingPosition.y = shootingPosition.y - 15;
                bullet = EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, shootingPosition, GameEngine::Vect2(15,0), 1);
                return ;
            } else {
                bullet = EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, shootingPosition, GameEngine::Vect2(20,0), 0);
            }
        } else if (shooterComp->typeBullet == BulletTypeEntity::EnemyBullet) {
            auto players = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
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
                auto velocity = directionToClosestPlayer * scaleFactor;
                bullet = EntityFactory::getInstance().createBaseEnemyBullet(componentsContainer, eventHandler, shootingPosition, velocity);
        }
        }
        eventHandler.queueEvent("PLAY_SOUND", bullet);
    }
}
