//
// Created by Theophilus Homawoo on 04/10/2023.
//

#include "RemoveHealth.hpp"

void RemoveHealth::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto [eventName, eventData] = eventHandler.getTriggeredEvent();
        size_t id = std::any_cast<size_t>(eventData);

        auto HealthComponentOpt = (componentsContainer.getComponent(id, GameEngine::ComponentsType::getComponentType("Health")));
        if (HealthComponentOpt.has_value()) {
            auto HealthComponent = std::dynamic_pointer_cast<Health>(HealthComponentOpt.value());
            HealthComponent->currentHealth -= 1;
            if (HealthComponent->currentHealth <= 0) {
                eventHandler.queueEvent("Death", id);
            }
            auto HealthBarId = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("IsHealthBar"));
            if (HealthBarId.size() > 0) {
                auto HealthBarComponentOpt = (componentsContainer.getComponent(HealthBarId[0], GameEngine::ComponentsType::getComponentType("SpriteComponent")));
                if (HealthBarComponentOpt.has_value()) {
                    auto HealthBarComponent = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(HealthBarComponentOpt.value());
                    HealthBarComponent->rect1.w = HealthComponent->currentHealth * 8;
                    if (HealthComponent->currentHealth > 3) {
                        HealthComponent->currentHealth = 3;
                        HealthBarComponent->rect1.w = 24;
                    }
                }
            }
        }
}