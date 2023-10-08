//
// Created by Theophilus Homawoo on 08/10/2023.
//

#include "CollisionHandler.hpp"
#include "IsBullet.hpp"

void CollisionHandler::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        call += 1;
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);

        auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        auto secondEntityOptPlayer = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));


        auto firstEntityOptBullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
        auto secondEntityOptBullet = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));

        auto firstEntityOptMob = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsMob"));
        auto secondEntityOptMob = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsMob"));

        std::cout << "Call: " << call << std::endl;
        std::cout << "Entities: " << firstEntity << " " << secondEntity << std::endl;
        std::cout << "Player: " << firstEntityOptPlayer.has_value() << " " << secondEntityOptPlayer.has_value() << std::endl;
        std::cout << "Bullet: " << firstEntityOptBullet.has_value() << " " << secondEntityOptBullet.has_value() << std::endl;
        std::cout << "Mob: " << firstEntityOptMob.has_value() << " " << secondEntityOptMob.has_value() << std::endl;
        std::cout << std::endl;

        // Player vs Bullet

        if (firstEntityOptPlayer.has_value() && secondEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*secondEntityOptBullet);

            if (!bullet->playerBullet) {
                eventHandler.queueEvent("PlayerHit");
                std::cout << "Player hit" << std::endl;
                componentsContainer.deleteEntity(secondEntity);
            }
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*firstEntityOptBullet);

            if (!bullet->playerBullet) {
                eventHandler.queueEvent("PlayerHit");
                std::cout << "Player hit" << std::endl;
                componentsContainer.deleteEntity(firstEntity);
            }
        }

        // Mob vs Bullet

        if (firstEntityOptMob.has_value() && secondEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*secondEntityOptBullet);

            if (bullet->playerBullet) {
                eventHandler.queueEvent("MobHit");
                std::cout << "Mob hit" << std::endl;
                componentsContainer.deleteEntity(secondEntity);
                componentsContainer.deleteEntity(firstEntity);

            }
        } else if (secondEntityOptMob.has_value() && firstEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*firstEntityOptBullet);

            if (bullet->playerBullet) {
                eventHandler.queueEvent("MobHit");
                std::cout << "Mob hit" << std::endl;
                componentsContainer.deleteEntity(firstEntity);
                componentsContainer.deleteEntity(secondEntity);
            }
        }

        // Player vs Mob

        if (firstEntityOptPlayer.has_value() && secondEntityOptMob.has_value()) {
            std::cout << "Player hit" << std::endl;
            eventHandler.queueEvent("PlayerHit");
            componentsContainer.deleteEntity(secondEntity);
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptMob.has_value()) {
            std::cout << "Player hit" << std::endl;
            eventHandler.queueEvent("PlayerHit");
            componentsContainer.deleteEntity(firstEntity);
        }

        // Bullet vs Bullet

        if (firstEntityOptBullet.has_value() && secondEntityOptBullet.has_value()) {
            componentsContainer.deleteEntity(firstEntity);
            componentsContainer.deleteEntity(secondEntity);
        }
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception caught!" << std::endl;
    }
}