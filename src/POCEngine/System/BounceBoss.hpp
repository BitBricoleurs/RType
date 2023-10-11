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
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include "WindowInfoComponent.hpp"

#include <cstddef>

class BounceBoss : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;

private:
  bool checkInScreen(size_t bossCore,
                     GameEngine::ComponentsContainer &container,
                     GameEngine::EventHandler &eventHandler);
  void getScreenSize(GameEngine::ComponentsContainer &componentsContainer);
  float randomizeVelocity(float currentVelocity);
  std::optional<GameEngine::Vect2>
  handleDirectionChange(GameEngine::Vect2 pos, GameEngine::Vect2 velocity);
  int sizeWidth = 0;
  int sizeHeight = 0;
  bool hasAppeared = false;
};
