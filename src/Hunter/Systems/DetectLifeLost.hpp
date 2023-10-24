/*
** EPITECH PROJECT, 2023
** RType
** File description:
** DetectLifeLost
*/

#pragma once

#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "PositionComponent2D.hpp"
#include "Score.hpp"
#include "VelocityComponent.hpp"

class DetectLifeLost : public GameEngine::ISystem {
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
