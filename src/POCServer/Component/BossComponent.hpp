/*
** EPITECH PROJECT, 2023
** RType
** File description:
** BossComponent
*/

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>

#pragma once

namespace Server {
class isBossCore : public GameEngine::AComponent {
public:
  isBossCore();

  size_t getComponentType() override;
};

class isBossPod : public GameEngine::AComponent {
public:
  isBossPod();

  size_t getComponentType() override;

  bool launched;
  unsigned int bounces;
};
}