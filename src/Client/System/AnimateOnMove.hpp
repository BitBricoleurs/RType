/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateOnMove
*/

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteAnimation.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"

namespace Client {

    class AnimateOnMove : public GameEngine::ISystem {
    public:
      void update(GameEngine::ComponentsContainer &componentsContainer,
                  GameEngine::EventHandler &eventHandler) override;
    };

}