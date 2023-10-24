/*
** EPITECH PROJECT, 2023
** RType
** File description:
** DeathAnimation
*/

#include "AComponent.hpp"
#include "Animation.hpp"
#include "ComponentsType.hpp"
#include "Vect2.hpp"
#include <cstddef>
#include <string>
#include <vector>

#pragma once

class DeathAnimation : public Animation {
public:
  DeathAnimation() = default;

  std::string filepath;
  std::vector<Utils::Vect2> spritePositions;

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("DeathAnimation");
  };
};