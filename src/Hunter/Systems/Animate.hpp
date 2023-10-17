/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animate
*/

#pragma once

#include "Animation.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"

class Animate : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
