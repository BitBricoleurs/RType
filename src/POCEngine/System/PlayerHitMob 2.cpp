//
// Created by Bartosz on 10/9/23.
//

#include "PlayerHitMob.hpp"


void PlayerHitMob::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
        auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        auto secondEntityOptMob = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsMob"));

        if (firstEntityOptPlayer.has_value()) {
            auto hpComponent = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("Health"));
            auto hpComponentCast = std::dynamic_pointer_cast<Health>(*hpComponent);
            hpComponentCast->currentHealth -= 1;
            if (hpComponentCast->currentHealth <= 0) {
                eventHandler.queueEvent("Death", firstEntity);
            }
            eventHandler.queueEvent("PLAY_SOUND", firstEntity);
            eventHandler.queueEvent("Death", secondEntity);
        } else if (secondEntityOptMob.has_value()) {
            auto hpComponent = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Health"));
            auto hpComponentCast = std::dynamic_pointer_cast<Health>(*hpComponent);
            hpComponentCast->currentHealth -= 1;
            if (hpComponentCast->currentHealth <= 0) {
                eventHandler.queueEvent("Death", secondEntity);
            }
            eventHandler.queueEvent("PLAY_SOUND", secondEntity);
            eventHandler.queueEvent("Death", firstEntity);
        }

    } catch (std::exception &e) {

    }
}