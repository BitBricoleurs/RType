//
// Created by Theophilus Homawoo on 08/10/2023.
//

#include "CollisionHandler.hpp"
#include "IsBullet.hpp"

namespace Client {

    void CollisionHandler::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            size_t firstEntity = 0;
            size_t secondEntity = 0;
            std::pair<size_t, size_t> data;
            try {
                data = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
                firstEntity = data.first;
                secondEntity = data.second;
            } catch (std::bad_any_cast &e) {
                return;
            }

            auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));
            auto secondEntityOptPlayer = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));


            auto firstEntityOptBullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
            auto secondEntityOptBullet = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));

            auto firstEntityOptMob = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsMob"));
            auto secondEntityOptMob = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsMob"));

            auto firstEntityOptPowerUp = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("isPowerUpPickUp"));
            auto secondEntityOptPowerUp = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("isPowerUpPickUp"));

            auto firstEntityOptForcePod = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsForcePod"));
            auto secondEntityOptForcePod = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsForcePod"));

            // Player vs Bullet

            if (firstEntityOptPlayer.has_value() && secondEntityOptBullet.has_value()) {
                auto bullet = std::static_pointer_cast<IsBullet>(*secondEntityOptBullet);

                if (!bullet->playerBullet) {
                    eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
                }
            } else if (secondEntityOptPlayer.has_value() && firstEntityOptBullet.has_value()) {
                auto bullet = std::static_pointer_cast<IsBullet>(*firstEntityOptBullet);

                if (!bullet->playerBullet) {
                    eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
                }
            }

            // Mob vs Bullet

            if (firstEntityOptMob.has_value() && secondEntityOptBullet.has_value()) {
                auto bullet = std::static_pointer_cast<IsBullet>(*secondEntityOptBullet);

                if (bullet->playerBullet && std::find(bullet->alreadyHit.begin(), bullet->alreadyHit.end(), firstEntity) == bullet->alreadyHit.end()) {
                    eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
                }
            } else if (secondEntityOptMob.has_value() && firstEntityOptBullet.has_value()) {
                auto bullet = std::static_pointer_cast<IsBullet>(*firstEntityOptBullet);

                if (bullet->playerBullet && std::find(bullet->alreadyHit.begin(), bullet->alreadyHit.end(), secondEntity) == bullet->alreadyHit.end()) {
                    eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
                }
            }

            // Player vs Mob

            if (firstEntityOptPlayer.has_value() && secondEntityOptMob.has_value()) {
                eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
            } else if (secondEntityOptPlayer.has_value() && firstEntityOptMob.has_value()) {
                eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
            }

            // Bullet vs Bullet

            if (firstEntityOptBullet.has_value() && secondEntityOptBullet.has_value()) {
                componentsContainer.deleteEntity(firstEntity);
                componentsContainer.deleteEntity(secondEntity);
            }


            // Player vs PowerUp

            if (firstEntityOptPlayer.has_value() && secondEntityOptPowerUp.has_value()) {
                auto poscompplayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                auto poscompplayercast = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(*poscompplayer);
                auto powerupcast = std::static_pointer_cast<isPowerUpPickUp>(*secondEntityOptPowerUp);
                if (powerupcast->powerUpType == 1)
                    eventHandler.queueEvent("ForcePodSpawn", poscompplayercast->pos.y);
                if (powerupcast->powerUpType == 2) {
                    auto shootercompplayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("Shooter"));
                    auto shootercompplayercast = std::static_pointer_cast<Shooter>(*shootercompplayer);
                    shootercompplayercast->typeBullet = 2;
                }

                componentsContainer.deleteEntity(secondEntity);
            } else if (secondEntityOptPlayer.has_value() && firstEntityOptPowerUp.has_value()) {
                auto poscompplayer = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                auto poscompplayercast = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(*poscompplayer);
                auto powerupcast = std::static_pointer_cast<isPowerUpPickUp>(*firstEntityOptPowerUp);
                if (powerupcast->powerUpType == 1)
                    eventHandler.queueEvent("ForcePodSpawn", poscompplayercast->pos.y);
                if (powerupcast->powerUpType == 2) {
                    auto shootercompplayer = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Shooter"));
                    auto shootercompplayercast = std::static_pointer_cast<Shooter>(*shootercompplayer);
                    shootercompplayercast->typeBullet = 2;
                }
                componentsContainer.deleteEntity(firstEntity);
            }
            // Player vs forcepod

            if (firstEntityOptPlayer.has_value() && secondEntityOptForcePod.has_value()) {
                eventHandler.queueEvent("ForcePodFix", firstEntity);
            } else if (secondEntityOptPlayer.has_value() && firstEntityOptForcePod.has_value()) {
                eventHandler.queueEvent("ForcePodFix", secondEntity);
            }


        } catch (const std::exception& e) {
            std::cout << "Standard exception: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown exception caught!" << std::endl;
        }
    }
}
