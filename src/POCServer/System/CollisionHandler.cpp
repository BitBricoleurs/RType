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

        auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        auto secondEntityOptPlayer = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));

        auto firstEntityOptBullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
        auto secondEntityOptBullet = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));

        auto firstEntityOptMob = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsMob"));
        auto secondEntityOptMob = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsMob"));

        auto firstEntityOptPowerUp = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPower"));
        auto secondEntityOptPowerUp = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsPower"));

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
            if (bullet->playerBullet && std::find(bullet->alreadyHit.begin(), bullet->alreadyHit.end(), firstEntity) == bullet->alreadyHit.end()) {
                eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
            }
        } else if (secondEntityOptMob.has_value() && firstEntityOptBullet.has_value()) {
            auto bullet = std::dynamic_pointer_cast<IsBullet>(*firstEntityOptBullet);
            if (bullet->playerBullet && std::find(bullet->alreadyHit.begin(), bullet->alreadyHit.end(), secondEntity) == bullet->alreadyHit.end()) {
                eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
            }
        }



        // Player vs Mob
        if(firstEntityOptPlayer.has_value() && secondEntityOptMob.has_value()) {
            eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptMob.has_value()) {
            eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
        }

        // Player vs PowerUp
        if (firstEntityOptPlayer.has_value() && secondEntityOptPowerUp.has_value()) {
            auto playerComp = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
            if (playerComp->entityIdForcePod == 0) {
                auto posCompPlayer = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
                eventHandler.queueEvent("ForcePodSpawn", posCompPlayer->pos.y);
            } else {
                // add weapon
            }
            componentsContainer.deleteEntity(secondEntity);
            std::vector<size_t> ids = {secondEntity};
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", ids, "", std::vector<std::any>{});
            std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allMessage);
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptPowerUp.has_value()) {
            auto playerComp = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
            if (playerComp->entityIdForcePod == 0) {
                auto posCompPlayer = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("PositionComponent2D")).value());
                eventHandler.queueEvent("ForcePodSpawn", posCompPlayer->pos.y);
            } else {
                // add weapon
            }
            componentsContainer.deleteEntity(firstEntity);
            std::vector<size_t> ids = {firstEntity};
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", ids, "", std::vector<std::any>{});
            std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allMessage);
        }

        // Player vs forcepod
        if (firstEntityOptPlayer.has_value() && secondEntityOptForcePod.has_value()) {
            auto playerComp = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
            auto forcePodComp = std::dynamic_pointer_cast<IsForcePod>(componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsForcePod")).value());
            if (forcePodComp->entityId == 0 && playerComp->entityIdForcePod == 0) {
                eventHandler.queueEvent("ForcePodFix", std::make_tuple(firstEntity, secondEntity));
            }
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptForcePod.has_value()) {
            auto playerComp = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
            auto forcePodComp = std::dynamic_pointer_cast<IsForcePod>(componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsForcePod")).value());
            if (forcePodComp->entityId == 0 && playerComp->entityIdForcePod == 0) {
                eventHandler.queueEvent("ForcePodFix", std::make_tuple(secondEntity, firstEntity));
            }
        }

    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception caught!" << std::endl;
    }
}

}
