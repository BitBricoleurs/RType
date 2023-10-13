/*
** EPITECH PROJECT, 2023
** RType
** File description:
** LaunchBossPods
*/

#pragma once

#include "BossComponent.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "PositionComponent2D.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include <cmath>

class LaunchBossPods : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
