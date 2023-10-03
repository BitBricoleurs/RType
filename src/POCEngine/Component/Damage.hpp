//
// Created by alexandre on 03/10/23.
//

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>
#pragma once

class Damage : public GameEngine::AComponent {
public:
  Damage(int damageValue);

  size_t getComponentType() override;

  int damageValue;
};
