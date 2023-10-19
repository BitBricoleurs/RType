//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include <vector>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "Vect2.hpp"

class DeathAnimation : public GameEngine::AComponent {
public:
  DeathAnimation();

  size_t getComponentType() override;

  int frameHeight, frameWidth;
  int currentFrameIndex;
  int frames;
  std::string filepath;
  Utils::Vect2 currentFrame;
  std::vector<Utils::Vect2> spritePositions;
};
