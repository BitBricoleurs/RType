//
// Created by alexandre on 04/10/23.
//

#include "VelocityComponent.hpp"
#include "ResetDirPlayer.hpp"

void ResetDirPlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
    for (const auto& entityID : entities) {
        auto event = eventHandler.getTriggeredEvent();
        auto player = componentsContainer.getComponentsFromEntity(entityID);
        auto velocityOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
        auto isPlayerOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        if (isPlayerOptional.has_value() && velocityOptional.has_value()) {
            auto velocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(velocityOptional.value());
            auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(isPlayerOptional.value());
             if (isPlayer->entityIdForcePod != 0) {
                auto velocityForcePodOpt = componentsContainer.getComponent(isPlayer->entityIdForcePod, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
                if (velocityForcePodOpt.has_value()) {
                    auto velocityForcePod = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(velocityForcePodOpt.value());
                    velocity->velocity.x = 0;
                    velocity->velocity.y = 0;
                    velocityForcePod->velocity.x = 0;
                    velocityForcePod->velocity.y = 0;
                }
            } else {
                 velocity->velocity.x = 0;
                 velocity->velocity.y = 0;
             }
        }
    }
}
