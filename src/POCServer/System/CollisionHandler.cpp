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

        auto firstEntityOptBossPod = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("isBossPod"));
        auto secondEntityOptBossPod = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("isBossPod"));

        auto secondEntityOptBossCore = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("isBossCore"));
        auto firstEntityOptBossCore = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("isBossCore"));

        // Player vs Bullet
        if (firstEntityOptPlayer.has_value() && secondEntityOptBullet.has_value()) {
            eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptBullet.has_value()) {
            eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
        }

        // Mob vs Bullet
        if (firstEntityOptMob.has_value() && secondEntityOptBullet.has_value()) {
            eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
        } else if (secondEntityOptMob.has_value() && firstEntityOptBullet.has_value()) {
            eventHandler.queueEvent("MobHit", std::make_pair(firstEntity, secondEntity));
        }

        // Player vs Mob
        if(firstEntityOptPlayer.has_value() && secondEntityOptMob.has_value()) {
            eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptMob.has_value()) {
            eventHandler.queueEvent("PlayerHit", std::make_pair(firstEntity, secondEntity));
        }

        // Player vs PowerUp
        if (firstEntityOptPlayer.has_value() && secondEntityOptPowerUp.has_value()) {
            auto isPlayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
            auto playerOpt = componentsContainer.getComponent(firstEntity, isPlayerType);
            if (!playerOpt.has_value())
                return;
            auto playerComp = std::static_pointer_cast<IsPlayer>(playerOpt.value());
            if (playerComp->entityIdForcePod == 0) {
                auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
                auto posCompPlayerOpt = componentsContainer.getComponent(firstEntity, positionType);
                if (!posCompPlayerOpt.has_value())
                    return;
                auto posCompPlayer = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posCompPlayerOpt.value());
                eventHandler.queueEvent("ForcePodSpawn", posCompPlayer->pos.y);
            } else {
                std::cout << "Manage power up" << std::endl;
                eventHandler.queueEvent("ManagePowerUp", firstEntity);
            }
            componentsContainer.deleteEntity(secondEntity);
            std::vector<size_t> ids = {secondEntity};
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", ids, "", std::vector<std::any>{});
            std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allMessage);
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptPowerUp.has_value()) {
            auto isPlayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
            auto playerOpt = componentsContainer.getComponent(secondEntity, isPlayerType);
            if (!playerOpt.has_value())
                return;
            auto playerComp = std::static_pointer_cast<IsPlayer>(playerOpt.value());
            if (playerComp->entityIdForcePod == 0) {
                auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
                auto posCompPlayerOpt = componentsContainer.getComponent(secondEntity, positionType);
                if (!posCompPlayerOpt.has_value())
                    return;
                auto posCompPlayer = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posCompPlayerOpt.value());
                eventHandler.queueEvent("ForcePodSpawn", posCompPlayer->pos.y);
            } else {
                eventHandler.queueEvent("ManagePowerUp", secondEntity);
            }
            componentsContainer.deleteEntity(firstEntity);
            std::vector<size_t> ids = {firstEntity};
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", ids, "", std::vector<std::any>{});
            std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
            eventHandler.queueEvent("SEND_NETWORK", allMessage);
        }

        // Player vs forcepod
        if (firstEntityOptPlayer.has_value() && secondEntityOptForcePod.has_value()) {
            auto playerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
            auto forcepodType = GameEngine::ComponentsType::getComponentType("IsForcePod");
            auto playerOpt = componentsContainer.getComponent(firstEntity, playerType);
            auto forcepodOpt = componentsContainer.getComponent(secondEntity, forcepodType);
            if (!playerOpt.has_value() || !forcepodOpt.has_value())
                return;
            auto playerComp = std::static_pointer_cast<IsPlayer>(playerOpt.value());
            auto forcePodComp = std::static_pointer_cast<IsForcePod>(forcepodOpt.value());
            if (forcePodComp->entityId == 0 && playerComp->entityIdForcePod == 0) {
                eventHandler.queueEvent("ForcePodFix", std::make_tuple(firstEntity, secondEntity));
            }
        } else if (secondEntityOptPlayer.has_value() && firstEntityOptForcePod.has_value()) {
            auto playerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
            auto forcepodType = GameEngine::ComponentsType::getComponentType("IsForcePod");
            auto playerOpt = componentsContainer.getComponent(secondEntity, playerType);
            auto forcepodOpt = componentsContainer.getComponent(firstEntity, forcepodType);
            if (!playerOpt.has_value() || !forcepodOpt.has_value())
                return;

            auto playerComp = std::static_pointer_cast<IsPlayer>(playerOpt.value());
            auto forcePodComp = std::static_pointer_cast<IsForcePod>(forcepodOpt.value());
            if (forcePodComp->entityId == 0 && playerComp->entityIdForcePod == 0) {
                eventHandler.queueEvent("ForcePodFix", std::make_tuple(secondEntity, firstEntity));
            }
        }

        // BossPod vs BossCore
        if (firstEntityOptBossCore.has_value() && secondEntityOptBossPod.has_value()) {
            auto bossPod = std::static_pointer_cast<isBossPod>(*secondEntityOptBossPod);
            if (bossPod->launched == true && bossPod->bounces > 2)
                eventHandler.queueEvent("LatchPodToBoss", std::make_pair(firstEntity, secondEntity));
        } else if (secondEntityOptBossCore.has_value() && firstEntityOptBossPod.has_value()) {
            auto bossPod = std::static_pointer_cast<isBossPod>(*firstEntityOptBossPod);
            if (bossPod->launched == true && bossPod->bounces > 2)
                eventHandler.queueEvent("LatchPodToBoss", std::make_pair(firstEntity, secondEntity));
        }

    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception caught!" << std::endl;
    }
}

}
