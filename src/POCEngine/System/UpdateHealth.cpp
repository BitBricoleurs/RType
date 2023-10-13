//
// Created by alexandre on 03/10/23.
//

#include "UpdateHealth.hpp"

void updateHealth::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        /*std::string event = eventHandler.getTriggeredEvent().first;
    size_t id = std::stoi(event.substr(1, event.find(" ")));

    auto healthOpt = componentsContainer.getComponent(
        id, GameEngine::ComponentsType::getComponentType("HealthComponent"));
    auto health = std::dynamic_pointer_cast<Health>(healthOpt.value());
    auto collisionsOpt = componentsContainer.getComponent(
        id, GameEngine::ComponentsType::getComponentType("CollideComponent"));
    auto collisions =
        std::dynamic_pointer_cast<CollideComponent>(collisionsOpt.value())
            ->collide;

    for (auto &collision : collisions) {
      auto damageOpt = componentsContainer.getComponent(
          collision, ComponentsType::getComponentType("DamageComponent"));
      auto damage =
          std::dynamic_pointer_cast<DamageComponent>(damageOpt.value());
      if (damage) {
        health->currentHealth -= damage->damageValue;
        if (health->currentHealth <= 0) {
          eventHandler.queueEvent("MobDeath " + std::to_string(id));
        }
      }
    }*/
}
