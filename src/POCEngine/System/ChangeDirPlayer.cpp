//
// Created by alexandre on 03/10/23.
//

#include "ChangeDirPlayer.hpp"
#include "VelocityComponent.hpp"

 void ChangeDirPlayer::update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) {

    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
    for (const auto& entityID : entities) {
        auto event = eventHandler.getTriggeredEvent();
        auto player = componentsContainer.getComponentsFromEntity(entityID);
        auto velocityOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
        if (velocityOptional.has_value()) {
             auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(velocityOptional.value());
            if (event.first == "UP_KEY_PRESSED") {
                velocity->velocity.y = -5;
            } else if (event.first == "DOWN_KEY_PRESSED") {
                velocity->velocity.y = 5;
            } else if (event.first == "LEFT_KEY_PRESSED") {
                velocity->velocity.x = -5;
            } else if (event.first == "RIGHT_KEY_PRESSED") {
                velocity->velocity.x = 5;
            }
        }
    }
  }
