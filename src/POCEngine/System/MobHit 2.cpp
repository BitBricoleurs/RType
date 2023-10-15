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
            auto hpComponentCast = std::dynamic_pointer_cast<Health>(*hpComponent);
            auto DamageBullet = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Damage"));
            auto DamageBulletCast = std::dynamic_pointer_cast<Damage>(*DamageBullet);
            hpComponentCast->currentHealth -= DamageBulletCast->damageValue;
            if (hpComponentCast->currentHealth <= 0) {
                eventHandler.queueEvent("Death", firstEntity);
            }
            componentsContainer.deleteEntity(secondEntity);
        } else {
            auto hpComponent = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Health"));
            auto hpComponentCast = std::dynamic_pointer_cast<Health>(*hpComponent);
            auto DamageBullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("Damage"));
            auto DamageBulletCast = std::dynamic_pointer_cast<Damage>(*DamageBullet);
            hpComponentCast->currentHealth -= DamageBulletCast->damageValue;
            if (hpComponentCast->currentHealth <= 0) {
                eventHandler.queueEvent("Death", secondEntity);
            }
            componentsContainer.deleteEntity(firstEntity);
        }
    } catch (std::exception &e) {

    }
}