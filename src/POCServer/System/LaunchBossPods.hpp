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
#include "Vect2.hpp"
#include "VelocityComponent.hpp"
#include "EntityFactory.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>

namespace Server {
class LaunchBossPods : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
} // namespace Server
