/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Score
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>

class Score : public GameEngine::AComponent {
public:
  Score() = default;

  size_t getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("Score");
  };
  int _score;
  int missed;
};