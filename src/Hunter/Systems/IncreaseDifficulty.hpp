/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IncreaseDifficulty
*/

#pragma once

#include "BaseVelocity.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"

class IncreaseDifficulty : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};