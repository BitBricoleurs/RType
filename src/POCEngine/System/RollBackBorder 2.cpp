//
// Created by alexandre on 09/10/23.
//

#include "RollBackBorder.hpp"

void RollBackBorder::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto windows = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("WindowInfoComponent"));
    size_t sizeWidth = 0;
    size_t sizeHeight = 0;

    for (const auto &window : windows) {
        auto windowOpt = componentsContainer.getComponent(window, GameEngine::ComponentsType::getComponentType("WindowInfoComponent"));
        if (windowOpt.has_value()) {
            auto windowSize = std::dynamic_pointer_cast<WindowInfoComponent>(windowOpt.value());
            sizeWidth = windowSize->windowWidth;
            sizeHeight = windowSize->windowHeight;
            break;
        }
    }

    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
    for (const auto& entityID : entities) {
        auto velocityOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
        auto positionOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto spriteOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));

        if (positionOptional.has_value() && velocityOptional.has_value() && spriteOptional.has_value()) {
            auto velocity = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(velocityOptional.value());
            auto position = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOptional.value());
            auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOptional.value());
            std::cout << "SIZE: " << sizeWidth << ":" << sizeHeight << std::endl;
            std::cout << "Pos: " << position->pos.x << ":" << position->pos.y << std::endl;
            if (position->pos.x + velocity->velocity.x < 0 || position->pos.x + velocity->velocity.x + (sprite->rect1.w * sprite->scale) > sizeWidth) {
                velocity->velocity.x = 0;
            }

            if (position->pos.y + velocity->velocity.y < 0 || position->pos.y + velocity->velocity.y + (sprite->rect1.h * sprite->scale) > sizeHeight) {
                velocity->velocity.y = 0;
            }
        }
    }
}
