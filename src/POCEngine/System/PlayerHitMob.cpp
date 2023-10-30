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
            eventHandler.queueEvent("DAMAGE", firstEntity);
            eventHandler.queueEvent("PLAY_SOUND", firstEntity);
            startMobDeath(componentsContainer, eventHandler, secondEntity);
            componentsContainer.unbindComponentFromEntity(secondEntity, GameEngine::ComponentsType::getComponentType("IsMob"));
        } else if (secondEntityOptMob.has_value()) {
            eventHandler.queueEvent("DAMAGE", secondEntity);
            eventHandler.queueEvent("PLAY_SOUND", secondEntity);
            startMobDeath(componentsContainer, eventHandler, firstEntity);
            componentsContainer.unbindComponentFromEntity(firstEntity, GameEngine::ComponentsType::getComponentType("IsMob"));
        }

    } catch (std::exception &e) {

    }
    }

    void PlayerHitMob::startMobDeath(GameEngine::ComponentsContainer &componentsContainer,
                           GameEngine::EventHandler &eventHandler, size_t id) {
  auto velocityOpt = componentsContainer.getComponent(
      id, GameEngine::ComponentsType::getComponentType("VelocityComponent"));

  auto velocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(
      velocityOpt.value());
  velocity->velocity.x = 0;
  velocity->velocity.y = 0;
  componentsContainer.unbindComponentFromEntity(
      id, GameEngine::ComponentsType::getComponentType("SpriteAnimation"));
  componentsContainer.unbindComponentFromEntity(
      id, GameEngine::ComponentsType::getComponentType("HeightVariation"));


  eventHandler.scheduleEvent("MobDeath", 5, id);
}
