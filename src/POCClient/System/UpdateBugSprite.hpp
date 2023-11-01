/*
** EPITECH PROJECT, 2023
** RType
** File description:
** UpdateBugSprite
*/

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "VelocityComponent.hpp"
#include "SpriteAnimation.hpp"
#include "MobComponents.hpp"
#include "SpriteComponent.hpp"

namespace Client {
    class UpdateBugSprite : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;
    };
}
