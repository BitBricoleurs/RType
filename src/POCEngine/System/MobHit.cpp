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
              startMobDeath(componentsContainer, eventHandler, firstEntity);
            }
            componentsContainer.deleteEntity(secondEntity);
        } else {
            auto hpComponent = componentsContainer.getComponent(secondEntity, GameEngine::ComponentsType::getComponentType("Health"));
            auto hpComponentCast = std::dynamic_pointer_cast<Health>(*hpComponent);
            auto DamageBullet = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("Damage"));
            auto DamageBulletCast = std::dynamic_pointer_cast<Damage>(*DamageBullet);
            hpComponentCast->currentHealth -= DamageBulletCast->damageValue;
            if (hpComponentCast->currentHealth <= 0) {
              startMobDeath(componentsContainer, eventHandler, secondEntity);
            }
            componentsContainer.deleteEntity(firstEntity);
        }
    } catch (std::exception &e) {

    }
}

void MobHit::startMobDeath(GameEngine::ComponentsContainer &componentsContainer,
                           GameEngine::EventHandler &eventHandler, size_t id) {
  auto velocityOpt = componentsContainer.getComponent(
      id, GameEngine::ComponentsType::getComponentType("VelocityComponent"));

  auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
      velocityOpt.value());
  //   velocity->velocity.x = 0;
  velocity->velocity.y = 0;
  componentsContainer.unbindComponentFromEntity(
      id, GameEngine::ComponentsType::getComponentType("SpriteAnimation"));
  componentsContainer.unbindComponentFromEntity(
      id, GameEngine::ComponentsType::getComponentType("HeightVariance"));

  eventHandler.scheduleEvent("MobDeath", 5, id);
}