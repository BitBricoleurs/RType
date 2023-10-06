/*
** EPITECH PROJECT, 2023
** RType
** File description:
** WiggleMob
*/

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "HeightVariation.hpp"
#include "ISystem.hpp"
#include "PositionComponent2D.hpp"

class WiggleMob : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};