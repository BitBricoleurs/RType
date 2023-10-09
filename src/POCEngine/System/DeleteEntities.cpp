//
// Created by alexandre on 05/10/23.
//

#include "DeleteEntities.hpp"
#include "WindowInfoComponent.hpp"

void DeleteEntities::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto windows = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("WindowInfoComponent"));
    size_t sizeWidth = 0;

    for (const auto &window : windows) {
        auto windowOpt = componentsContainer.getComponent(window, GameEngine::ComponentsType::getComponentType("WindowInfoComponent"));
        if (windowOpt.has_value()) {
            auto windowSize = std::dynamic_pointer_cast<WindowInfoComponent>(windowOpt.value());
            sizeWidth = windowSize->windowWidth;
            break;
        }
    }

    auto bulletEntities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsBullet"));
    for (const auto &entityID : bulletEntities) {
        deleteBulletIfOutOfBounds(entityID, sizeWidth, componentsContainer);
    }

    auto mobEntities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsMob"));
    for (const auto &entityID : mobEntities) {
        deleteMobParallaxIfOutsideLeft(entityID, componentsContainer);
    }

    auto parallaxEntities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsParallax"));
    for (const auto &entityID : parallaxEntities) {
        deleteMobParallaxIfOutsideLeft(entityID, componentsContainer);
    }
}

void DeleteEntities::deleteBulletIfOutOfBounds(const size_t& entityID, size_t sizeWidth, GameEngine::ComponentsContainer &componentsContainer)
{
    auto posOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
    if (posOpt.has_value() && spriteOpt.has_value()) {
        auto pos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(posOpt.value());
        auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());
        if (pos->pos.x + sprite->rect1.w < 0 || pos->pos.x > sizeWidth) {
            componentsContainer.deleteEntity(entityID);
        }
    }
}

void DeleteEntities::deleteMobParallaxIfOutsideLeft(const size_t& entityID, GameEngine::ComponentsContainer &componentsContainer)
{
    auto posOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
    if (posOpt.has_value() && spriteOpt.has_value()) {
        auto pos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(posOpt.value());
        auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());
        if (pos->pos.x + sprite->rect1.w < 0) {
            componentsContainer.deleteEntity(entityID);
        }
    }
}

