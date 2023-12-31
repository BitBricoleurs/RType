/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GameOver
*/

#pragma once

#include "ButtonComponent.hpp"
#include "ColorR.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "PositionComponent2D.hpp"
#include "Vect2.hpp"

class GameOver : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
