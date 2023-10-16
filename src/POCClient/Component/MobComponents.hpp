/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobsIdComponents
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>

class PataPata : public GameEngine::AComponent {
public:
  PataPata() = default;

  size_t getComponentType() override;
};

class Cancer : public GameEngine::AComponent {
public:
  Cancer() = default;

  size_t getComponentType() override;
};

class Bug : public GameEngine::AComponent {
public:
  Bug() = default;

  size_t getComponentType() override;
};
