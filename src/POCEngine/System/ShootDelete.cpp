//
// Created by alexandre on 05/10/23.
//

#include "ShootDelete.hpp"
#include "WindowInfoComponent.hpp"

void ShootDelete::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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
    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsBullet"));
    for (const auto &entityID : entities) {
        auto posOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (posOpt.has_value() && spriteOpt.has_value()) {
            auto pos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(posOpt.value());
            auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());
            if (pos->pos.x + sprite->rect1.w < 0 || pos->pos.x > sizeWidth) {
                std::cout << "DELETE" << std::endl;
                componentsContainer.deleteEntity(entityID);
            }

        }
    }
}
