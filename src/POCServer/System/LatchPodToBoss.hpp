/*
** EPITECH PROJECT, 2023
** RType
** File description:
** LatchPodToBoss
*/

#pragma once

#include "BossComponent.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "VelocityComponent.hpp"
#include <cmath>

namespace Server {

class LatchPodToBoss : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;
};
} // namespace Server
