/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CurveDown
*/

#pragma once

#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "VelocityComponent.hpp"

class CurveDown : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
