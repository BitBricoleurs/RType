/*
** EPITECH PROJECT, 2023
** RType
** File description:
** HeightVariation
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>

class HeightVariation : public GameEngine::AComponent {
public:
  HeightVariation(float heightVarience, float maxVar, float baseY)
      : heightVarience(heightVarience), maxVar(maxVar), baseY(baseY),
        isGoingUp(true) {}

  size_t getComponentType() override;
  float baseY;
  float heightVarience;
  float maxVar;
  bool isGoingUp;
};