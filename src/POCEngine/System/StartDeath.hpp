/*
** EPITECH PROJECT, 2023
** RType
** File description:
** StartDeath
*/

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteAnimation.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"

class StartDeath : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
