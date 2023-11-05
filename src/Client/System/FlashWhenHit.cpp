/*
** EPITECH PROJECT, 2023
** RType
** File description:
** FlashWhenHit
*/

#include "FlashWhenHit.hpp"

void Client::FlashWhenHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto entityID = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
        auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));

        if (spriteOpt.has_value()) {
            auto sprite = std::dynamic_pointer_cast<RenderEngine::SpriteComponent>(spriteOpt.value());
            if (sprite->flash) {
                sprite->isVisible = !sprite->isVisible;
                sprite->flashtimer++;
            }
            if (sprite->flashtimer >= 5) {
                sprite->flash = false;
                sprite->flashtimer = 0;
            }
        }
    } catch (const std::bad_any_cast&) {
        std::cerr << "Cast error in FlashWhenHit::update" << std::endl;
    }
}
