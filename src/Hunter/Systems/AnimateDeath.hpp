/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateDeath
*/

#pragma once

#include "ButtonComponent.hpp"
#include "ComponentsType.hpp"
#include "DeathAnimation.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"

class AnimateDeath : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
