//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>

class Health : public GameEngine::AComponent {
public:
  Health(int maxHealth);
  size_t getComponentType() override;

  int maxHealth;
  int currentHealth;
};
