//
// Created by alexandre on 03/10/23.
//

#include "Shoot.hpp"
#include "MovementComponent2D.hpp"
#include "Shooter.hpp"
#include "Vect2.hpp"
#include "IsBullet.hpp"
#include "VelocityComponent.hpp"
#include <cmath>

namespace Server {

    void Shoot::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
        std::vector<size_t> gameStateEntities = componentsContainer.getEntitiesWithComponent(compTypeGameState);
        if (gameStateEntities.empty())
            return;
        auto compMay = componentsContainer.getComponent(gameStateEntities[0], compTypeGameState);
        if (!compMay.has_value())
            return;
        auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
        if (gameStateComp->_state != Utils::GameState::State::RUNNING)
            return;
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

       if (positionOptional.has_value() && shooterOptional.has_value()) {
            auto posComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionOptional.value());
            auto shooterComp = std::static_pointer_cast<Shooter>(shooterOptional.value());

            Utils::Vect2 shootingPosition(posComp->pos.x + shooterComp->shootPosition.x, posComp->pos.y + shooterComp->shootPosition.y);
            if (shooterComp->typeBullet == BulletTypeEntity::PlayerBullet) {
                if (charge >= 20) {
                    shootingPosition.y = shootingPosition.y - 15;
                    size_t chargeValue = ((charge - 20) / 20 + 1);
                    if (charge == 100)
                        chargeValue = 5;
                    EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, shootingPosition, Utils::Vect2(25,0), chargeValue);
                } else {
                    EntityFactory::getInstance().createPlayerBullet(componentsContainer, eventHandler, shootingPosition, Utils::Vect2(20,0), 0);
                }
            } else if (shooterComp->typeBullet == BulletTypeEntity::EnemyBullet) {
                auto players = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
                float closestDistance = std::numeric_limits<float>::max();
                Utils::Vect2 directionToClosestPlayer;
                for (auto &player : players) {
                    auto positionOpt = componentsContainer.getComponent(player, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                    auto positionComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionOpt.value());
                    if (positionComp) {
                        Utils::Vect2 directionToPlayer = positionComp->pos - shootingPosition;
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
                    EntityFactory::getInstance().createBaseEnemyBullet(componentsContainer, eventHandler, shootingPosition, velocity);
            }
            }
        }
    }
}
