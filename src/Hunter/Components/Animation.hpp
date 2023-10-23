/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animation
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Vect2.hpp"
#include <cstddef>

class Animation : public GameEngine::AComponent {
public:
  Animation() = default;

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("Animation");
  };

  int frameHeight, frameWidth;
  bool twoDirections;
  int currentFrameIndex;
  int frames;
  Utils::Vect2 currentFrame;
  std::vector<Utils::Vect2> spritePositionsLeft;
  std::vector<Utils::Vect2> spritePositionsRight;
};