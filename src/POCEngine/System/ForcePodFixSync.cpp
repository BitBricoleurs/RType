//
// Created by alexandre on 05/10/23.
//

#include "ForcePodFixSync.hpp"

void ForcePodFixSync::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsForcePod"));
    for (const auto& entityID : entities) {
        auto isForcePodOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("IsForcePod"));
        auto posPodForceOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto spritePodForceOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (isForcePodOptional.has_value() && posPodForceOptional.has_value() && spritePodForceOptional.has_value()) {
            auto forcePod = std::dynamic_pointer_cast<IsForcePod>(isForcePodOptional.value());
            auto forcePodPos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(posPodForceOptional.value());
            auto forcePodSprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spritePodForceOptional.value());
            auto entityIdPlayer = forcePod->entityId;
            auto positionOpt = componentsContainer.getComponent(entityIdPlayer, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
            auto spriteOpt = componentsContainer.getComponent(entityIdPlayer, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
            if (positionOpt.has_value() && spriteOpt.has_value()) {
                auto pos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOpt.value());
                auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());
                forcePodPos->pos.x = pos->pos.x + sprite->rect1.w;
                forcePodPos->pos.y = pos->pos.y + ((sprite->rect1.h / 2) - (forcePodSprite->rect1.h / 2));
            }
        }
    }
}
