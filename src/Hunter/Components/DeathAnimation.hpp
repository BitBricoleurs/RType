/*
** EPITECH PROJECT, 2023
** RType
** File description:
** DeathAnimation
*/

#include "AComponent.hpp"
#include "Animation.hpp"
#include "ComponentsType.hpp"
#include <cstddef>
#include <string>

#pragma once

class DeathAnimation : public Animation {
public:
  DeathAnimation() = default;

  std::string filepath;
  std::vector<GameEngine::Vect2> spritePositions;

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("DeathAnimation");
  };
};