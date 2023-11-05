/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Bird
*/

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>

#pragma once

class Bird : public GameEngine::AComponent {
public:
  Bird() = default;

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("Bird");
  };
};
