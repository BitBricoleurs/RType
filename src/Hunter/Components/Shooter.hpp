/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Shooter
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Utils.hpp"
#include <cstddef>

class Shooter : public GameEngine::AComponent {
public:
  Shooter() = default;

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("Shooter");
  };
};