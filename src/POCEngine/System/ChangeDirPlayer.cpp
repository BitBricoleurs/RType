//
// Created by alexandre on 03/10/23.
//

#include "ChangeDirPlayer.hpp"
#include "VelocityComponent.hpp"

 void ChangeDirPlayer::update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) {

    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
    for (const auto& entityID : entities) {
        auto event = eventHandler.getTriggeredEvent();
        auto velocityOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
        auto isPlayerOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        if (velocityOptional.has_value() && isPlayerOptional.has_value()) {
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityOptional.value());
            auto isPlayer = std::static_pointer_cast<IsPlayer>(isPlayerOptional.value());
            float speed = 7.0;
            if (isPlayer->entityIdForcePod != 0) {
                auto velocityForcePodOpt = componentsContainer.getComponent(isPlayer->entityIdForcePod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
                if (velocityForcePodOpt.has_value()) {
                    auto velocityForcePod = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityForcePodOpt.value());
                    if (event.first == "UP_KEY_PRESSED") {
                        velocityForcePod->velocity.y = -speed;
                    } else if (event.first == "DOWN_KEY_PRESSED") {
                        velocityForcePod->velocity.y = speed;
                    } else if (event.first == "LEFT_KEY_PRESSED") {
                        velocityForcePod->velocity.x = -speed;
                    } else if (event.first == "RIGHT_KEY_PRESSED") {
                        velocityForcePod->velocity.x = speed;
                    }
                }
            }
            if (event.first == "UP_KEY_PRESSED") {
                     velocity->velocity.y = -speed;
            } else if (event.first == "DOWN_KEY_PRESSED") {
                     velocity->velocity.y = speed;
            } else if (event.first == "LEFT_KEY_PRESSED") {
                     velocity->velocity.x = -speed;
            } else if (event.first == "RIGHT_KEY_PRESSED") {
                     velocity->velocity.x = speed;
            } 
        }
    }
}
