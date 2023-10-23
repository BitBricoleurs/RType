/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BaseVelocity
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Vect2.hpp"
#include <cstddef>

class BaseVelocity : public GameEngine::AComponent {
public:
  BaseVelocity(const Utils::Vect2 &velocity) : velocity(velocity) {}

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("BaseVelocity");
  };
  Utils::Vect2 velocity;
};
