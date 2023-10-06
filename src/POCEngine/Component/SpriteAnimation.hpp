//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include <vector>
#include "Utils.hpp"
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class SpriteAnimation : public GameEngine::AComponent {
public:
  SpriteAnimation();

  size_t getComponentType() override;

  int frameHeight, frameWidth;
  bool twoDirections;
  int currentFrameIndex;
  int frames;
  GameEngine::Vect2 currentFrame;
  std::vector<GameEngine::Vect2> spritePositionsLeft;
  std::vector<GameEngine::Vect2> spritePositionsRight;
};

class ChargeShootAnimation : public GameEngine::AComponent {
public:
  ChargeShootAnimation();

  size_t getComponentType() override;

  int frameHeight, frameWidth;
  int currentFrameIndex;
  int frames;
  GameEngine::Vect2 currentFrame;
  std::vector<GameEngine::Vect2> spritePositionsLeft;
  std::vector<GameEngine::Vect2> spritePositionsRight;
};