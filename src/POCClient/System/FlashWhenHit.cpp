/*
** EPITECH PROJECT, 2023
** RType
** File description:
** FlashWhenHit
*/

#include "FlashWhenHit.hpp"

void Client::FlashWhenHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    
    auto entityID = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
    auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));

    if (spriteOpt.has_value()) {
        auto sprite = std::dynamic_pointer_cast<RenderEngine::SpriteComponent>(spriteOpt.value());
        if (!sprite->flash) {
            sprite->tint = {255, 255, 255, 255};
            sprite->flash = true;
        } else {
            sprite->tint = {255, 255, 255, 0};
            sprite->flash = false;
        }
    }
}