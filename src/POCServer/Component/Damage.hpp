//
// Created by alexandre on 03/10/23.
//

#include <cstddef>
#include "AComponent.hpp"
#include "ComponentsType.hpp"

#pragma once

class Damage : public GameEngine::AComponent {
public:
  Damage(int damageValue);

  size_t getComponentType() override;

  int damageValue;
};
