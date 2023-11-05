/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Game
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>

class Game : public GameEngine::AComponent {
public:
  Game() = default;

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("Game");
  };
};