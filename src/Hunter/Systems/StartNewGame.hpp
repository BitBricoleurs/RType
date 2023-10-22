/*
** EPITECH PROJECT, 2023
** RType
** File description:
** StartNewGame
*/

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "Score.hpp"

class StartNewGame : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
