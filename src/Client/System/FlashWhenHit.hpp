/*
** EPITECH PROJECT, 2023
** RType
** File description:
** FlashWhenHit
*/

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "SpriteComponent.hpp"

namespace Client {

    class FlashWhenHit : public GameEngine::ISystem {
    public:
        FlashWhenHit() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}