/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnBird
*/

#pragma once

#include "Animation.hpp"
#include "AudioComponent.hpp"
#include "Bird.hpp"
#include "ButtonComponent.hpp"
#include "ColorR.hpp"
#include "ComponentsType.hpp"
#include "DeathAnimation.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "MovementComponent2D.hpp"
#include "PositionComponent2D.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "Vect2.hpp"
#include "VelocityComponent.hpp"
#include "rect.hpp"
#include <BaseVelocity.hpp>
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

  static std::shared_ptr<DeathAnimation>
  initDeathAnimation(const std::string &filepath, int frames, int width,
                     int height);

  static Utils::Vect2 getRandomPosition();
};
