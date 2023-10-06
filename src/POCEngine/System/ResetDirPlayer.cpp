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
        if (velocityOptional.has_value()) {
             auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(velocityOptional.value());
             velocity->velocity.x = 0;
             velocity->velocity.y = 0;
        }
    }
}
