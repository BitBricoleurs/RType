/*
** EPITECH PROJECT, 2023
** RType
** File description:
** FlashWhenHit
*/

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteComponent.hpp"

class FlashWhenHit : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
