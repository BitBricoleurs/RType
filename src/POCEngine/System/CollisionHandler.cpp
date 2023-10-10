//
// Created by Theophilus Homawoo on 08/10/2023.
//

#include "CollisionHandler.hpp"
#include "IsBullet.hpp"

void CollisionHandler::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);

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
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*secondEntityOptBullet);

            if (!bullet->playerBullet) {
                eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
            }
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*firstEntityOptBullet);

            if (!bullet->playerBullet) {
                eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
            }
        }

        // Mob vs Bullet

        if (firstEntityOptMob.has_value() && secondEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*secondEntityOptBullet);

            if (bullet->playerBullet) {
                eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
            }
        } else if (secondEntityOptMob.has_value() && firstEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*firstEntityOptBullet);

            if (bullet->playerBullet) {
                eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
            }
        }

        // Player vs Mob

        if (firstEntityOptPlayer.has_value() && secondEntityOptMob.has_value()) {
            eventHandler.queueEvent("PlayerHitMob", std::make_pair(firstEntity, secondEntity));
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptMob.has_value()) {
            eventHandler.queueEvent("PlayerHitMob", std::make_pair(firstEntity, secondEntity));
        }

        // Bullet vs Bullet

        if (firstEntityOptBullet.has_value() && secondEntityOptBullet.has_value()) {
            componentsContainer.deleteEntity(firstEntity);
            componentsContainer.deleteEntity(secondEntity);
        }


        // Player vs PowerUp

        if (firstEntityOptPlayer.has_value() && secondEntityOptPowerUp.has_value()) {
            auto poscompplayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
            auto poscompplayercast = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(*poscompplayer);
            eventHandler.queueEvent("ForcePodSpawn", poscompplayercast->pos.y);
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptPowerUp.has_value()) {
            auto poscompplayer = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
            auto poscompplayercast = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(*poscompplayer);
            eventHandler.queueEvent("ForcePodSpawn", poscompplayercast->pos.y);
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