/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnBird
*/

#pragma once

#include "Animation.hpp"
#include "Bird.hpp"
#include "ButtonComponent.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "MovementComponent2D.hpp"
#include "PositionComponent2D.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "VelocityComponent.hpp"
#include <cstddef>

class SpawnBird : public GameEngine::ISystem {
public:
  void update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) override;

private:
  size_t createBird(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler);

  static std::shared_ptr<Animation> initAnimation(int frames, int width,
                                                  int height,
                                                  bool twoDirections,
                                                  int direction);
};
