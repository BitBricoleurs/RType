/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BounceBoss
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
#include <cstddef>

namespace Server {
class BounceBoss : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;

private:
  bool checkInScreen(size_t bossCore,
                     GameEngine::ComponentsContainer &container,
                     GameEngine::EventHandler &eventHandler);
  float randomizeVelocity(float currentVelocity);
  std::optional<Utils::Vect2> handleDirectionChange(Utils::Vect2 pos,
                                                    Utils::Vect2 velocity);
  size_t sizeWidth = 1920;
  size_t sizeHeight = 1080;
  bool hasAppeared = false;
};
} // namespace Server