/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ChargeShoot
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <cstddef>

class ChargeShoot : public GameEngine::AComponent {
public:
  ChargeShoot() = default;

  size_t getComponentType() override;
  size_t player;
  size_t charge;
};
