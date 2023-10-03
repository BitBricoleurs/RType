//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>

class DeathAnimation : public GameEngine::AComponent {
public:
  DeathAnimation();

  size_t getComponentType() override;

  int frameHeight, frameWidth;
  int currentFrameIndex;
  int frames;
  GameEngine::Vect2 currentFrame;
  std::vector<GameEngine::Vect2> spritePositions;
};
