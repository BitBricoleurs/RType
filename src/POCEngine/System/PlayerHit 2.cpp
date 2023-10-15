//
// Created by Bartosz on 10/9/23.
//

#include "PlayerHit.hpp"

void PlayerHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
        auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));

        if (firstEntityOptPlayer.has_value()) {
            auto hpComponent = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("Health"));
            auto hpComponentCast = std::dynamic_pointer_cast<Health>(*hpComponent);
            hpComponentCast->currentHealth -= 1;
            if (hpComponentCast->currentHealth <= 0) {
                eventHandler.queueEvent("Death", firstEntity);
            }
            eventHandler.queueEvent("PLAY_SOUND", firstEntity);
            componentsContainer.deleteEntity(secondEntity);
        } else {
            auto hpComponent = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Health"));
            auto hpComponentCast = std::dynamic_pointer_cast<Health>(*hpComponent);
                hpComponentCast->currentHealth -= 1;
            if (hpComponentCast->currentHealth <= 0) {
                eventHandler.queueEvent("Death", secondEntity);
            }
            eventHandler.queueEvent("PLAY_SOUND", secondEntity);
            componentsContainer.deleteEntity(firstEntity);
        }

    } catch (std::exception &e) {

    }
}