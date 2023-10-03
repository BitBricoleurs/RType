//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>

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
