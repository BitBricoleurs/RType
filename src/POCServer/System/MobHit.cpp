//
// Created by Bartosz on 10/9/23.
//

#include "MobHit.hpp"

void MobHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
        auto firstEntityOptMob = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsMob"));
        if (firstEntityOptMob.has_value()) {
            auto hpComponent = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("Health"));
            if (!hpComponent.has_value())
                return;
            auto hpComponentCast = std::static_pointer_cast<Health>(hpComponent.value());
            auto DamageBullet = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Damage"));
            if (DamageBullet.has_value()) {
                auto DamageBulletCast = std::dynamic_pointer_cast<Damage>(*DamageBullet);
                if (DamageBulletCast != nullptr)
                    hpComponentCast->currentHealth -= DamageBulletCast->damageValue;
            }
            if (hpComponentCast->currentHealth <= 0) {
                auto ispowerup = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPowerUp"));
                if (ispowerup.has_value())
                    eventHandler.queueEvent("SpawnPowerUp", firstEntity);
                std::vector<size_t> ids = {firstEntity};
                killMobNetwork(eventHandler, ids);
                componentsContainer.deleteEntity(firstEntity);
            }
            auto isbullet = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
            if (isbullet.has_value()) {
                auto isbulletcast = std::static_pointer_cast<IsBullet>(isbullet.value());
                if (isbulletcast->passingThrough == false) {
                    std::vector<size_t> idsBullet = {secondEntity};
                    killMobNetwork(eventHandler, idsBullet);
                    componentsContainer.deleteEntity(secondEntity);
                }

            }
        } else {
            auto hpComponent = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Health"));
            if (!hpComponent.has_value())
                return;
            auto hpComponentCast = std::static_pointer_cast<Health>(hpComponent.value());
            auto DamageBullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("Damage"));
            if (DamageBullet.has_value()) {
                auto DamageBulletCast = std::dynamic_pointer_cast<Damage>(DamageBullet.value());
                if (DamageBulletCast != nullptr)
                    hpComponentCast->currentHealth -= DamageBulletCast->damageValue;
            }
            if (hpComponentCast->currentHealth <= 0) {
                auto ispowerup = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("IsPowerUp"));
                if (ispowerup.has_value())
                    eventHandler.queueEvent("SpawnPowerUp", secondEntity);
                std::vector<size_t> ids = {secondEntity};
                killMobNetwork(eventHandler, ids);
                componentsContainer.deleteEntity(secondEntity);
            }
            auto isbullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
            if (isbullet.has_value()) {
                auto isbulletcast = std::static_pointer_cast<IsBullet>(*isbullet);
                if (isbulletcast->passingThrough == false) {
                    componentsContainer.deleteEntity(firstEntity);
                    std::vector<size_t> idsBullet = {firstEntity};
                    killMobNetwork(eventHandler, idsBullet);
                }
            }
        }
    } catch (std::exception &e) {

    }
}

void MobHit::killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill)
{
     std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToKill, "", std::vector<std::any>{});
     std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
     eventHandler.queueEvent("SEND_NETWORK", allMessage);
}