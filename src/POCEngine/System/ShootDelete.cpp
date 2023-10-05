//
// Created by alexandre on 05/10/23.
//

#include "ShootDelete.hpp"

void ShootDelete::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsBullet"));
    for (const auto &entityID : entities) {
        auto posOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (posOpt.has_value() && spriteOpt.has_value()) {
            auto pos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(posOpt.value());
            auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());

        }
    }
}