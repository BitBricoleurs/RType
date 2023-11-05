//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class Health : public GameEngine::AComponent {
public:
  Health(int maxHealth);
  size_t getComponentType() override;

  int maxHealth;
  int currentHealth;
};