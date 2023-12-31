//
// Created by Theophilus Homawoo on 11/10/2023.
//

#include "SyncPosSprite.hpp"

void Client::SyncPosSprite::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto entitiesWithMovement = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("MovementComponent2D"));

    for (const auto& entityID : entitiesWithMovement) {
        auto positionOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto spriteOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));

        if (positionOptional.has_value() && spriteOptional.has_value()) {
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionOptional.value());
            auto sprite = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteOptional.value());

            if (position && sprite) {
                sprite->pos = position->pos;
            }
        }
    }
}
