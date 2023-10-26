//
// Created by Theophilus Homawoo on 08/10/2023.
//

#include "CollisionHandler.hpp"
#include "IsBullet.hpp"
#include "IsPlayer.hpp"

namespace Server {

void CollisionHandler::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);

        auto getComponent = [&](size_t entity, const std::string& componentName) {
            return componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType(componentName));
        };

        auto checkCollision = [=](const std::string& componentName1, const std::string& componentName2) {
            return getComponent(firstEntity, componentName1).has_value() && getComponent(secondEntity, componentName2).has_value();
        };

        // Player vs Bullet
        if (checkCollision("IsPlayer", "IsBullet") || checkCollision("IsBullet", "IsPlayer")) {
            auto bulletOpt = checkCollision("IsPlayer", "IsBullet") ? getComponent(secondEntity, "IsBullet") : getComponent(firstEntity, "IsBullet");
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*bulletOpt);
            if (!bullet->playerBullet) {
                eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
            }
        }

        // Mob vs Bullet
        if (checkCollision("IsMob", "IsBullet") || checkCollision("IsBullet", "IsMob")) {
            auto bulletOpt = checkCollision("IsMob", "IsBullet") ? getComponent(secondEntity, "IsBullet") : getComponent(firstEntity, "IsBullet");
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*bulletOpt);
            auto mobEntity = checkCollision("IsMob", "IsBullet") ? firstEntity : secondEntity;
            if (bullet->playerBullet && std::find(bullet->alreadyHit.begin(), bullet->alreadyHit.end(), mobEntity) == bullet->alreadyHit.end()) {
                eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
            }
        }

        // Player vs Mob
        if (checkCollision("IsPlayer", "IsMob") || checkCollision("IsMob", "IsPlayer")) {
            eventHandler.queueEvent("PlayerHitMob", std::make_pair(firstEntity, secondEntity));
        }

        // Bullet vs Bullet collision
        if (checkCollision("IsBullet", "IsBullet")) {
            //componentsContainer.deleteEntity(firstEntity);
            //componentsContainer.deleteEntity(secondEntity);
        }

        // Player vs PowerUp
        if (checkCollision("IsPlayer", "IsPower") || checkCollision("IsPower", "IsPlayer")) {
            size_t playerEntity = checkCollision("IsPlayer", "IsPower") ? firstEntity : secondEntity;
            auto powerEntity = checkCollision("IsPlayer", "IsPower") ? secondEntity : firstEntity;
            auto playerComp = std::dynamic_pointer_cast<IsPlayer>(*getComponent(playerEntity, "IsPlayer"));

            if (playerComp->entityIdForcePod == 0) {
                auto posCompPlayer = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(*getComponent(playerEntity, "PositionComponent2D"));
                eventHandler.queueEvent("ForcePodSpawn", posCompPlayer->pos.y);
            } else {
                std::cout << "Enter PowerUp else statement" << std::endl;
                // add weapon
            }
            componentsContainer.deleteEntity(powerEntity);
            std::vector<size_t> ids = {powerEntity};
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", ids, "", std::vector<std::any>{});
            std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allMessage);
        }

        // Player vs forcepod
        if (checkCollision("IsPlayer", "IsForcePod") || checkCollision("IsForcePod", "IsPlayer")) {
            size_t playerEntity = checkCollision("IsPlayer", "IsForcePod") ? firstEntity : secondEntity;
            size_t forcePodEntity = checkCollision("IsPlayer", "IsForcePod") ? secondEntity : firstEntity;
            auto isForcePod = std::dynamic_pointer_cast<IsForcePod>(*getComponent(forcePodEntity, "IsForcePod"));
            if (isForcePod->entityId == 0) {
                eventHandler.queueEvent("ForcePodFix", std::make_tuple(playerEntity, forcePodEntity));
            }
        }

    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception caught!" << std::endl;
    }
}

}
