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
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <cmath>

namespace Client {
    class UpdateBugSprite : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;
    };
}
