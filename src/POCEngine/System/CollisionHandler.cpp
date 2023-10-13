//
// Created by Theophilus Homawoo on 08/10/2023.
//

#include "CollisionHandler.hpp"
#include "BossComponent.hpp"
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

        auto firstEntityOptBossPod = componentsContainer.getComponent(
            firstEntity,
            GameEngine::ComponentsType::getComponentType("isBossPod"));
        auto secondEntityOptBossPod = componentsContainer.getComponent(
            secondEntity,
            GameEngine::ComponentsType::getComponentType("isBossPod"));

        auto secondEntityOptBossCore = componentsContainer.getComponent(
            secondEntity,
            GameEngine::ComponentsType::getComponentType("isBossCore"));
        auto firstEntityOptBossCore = componentsContainer.getComponent(
            firstEntity,
            GameEngine::ComponentsType::getComponentType("isBossCore"));

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

        // BossPod vs BossCore
        if (firstEntityOptBossCore.has_value() &&
            secondEntityOptBossPod.has_value()) {
          auto bossPod =
              std::dynamic_pointer_cast<isBossPod>(*secondEntityOptBossPod);
          if (bossPod->launched == true && bossPod->bounces > 2) {
            eventHandler.queueEvent("LatchPodToBoss",
                                    std::make_pair(firstEntity, secondEntity));
          }
        } else if (secondEntityOptBossCore.has_value() &&
                   firstEntityOptBossPod.has_value()) {
          auto bossPod =
              std::dynamic_pointer_cast<isBossPod>(*firstEntityOptBossPod);
          if (bossPod->launched == true && bossPod->bounces > 2) {
            eventHandler.queueEvent("LatchPodToBoss",
                                    std::make_pair(firstEntity, secondEntity));
          }
        }

    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception caught!" << std::endl;
    }
}