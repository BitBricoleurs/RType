/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AnimateShot
*/

#pragma once

#include "Animation.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "SpriteComponent.hpp"

class AnimateShot : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
