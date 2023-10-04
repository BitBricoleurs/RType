//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsBullet : public GameEngine::AComponent {
public:
  IsBullet() = default;

  size_t getComponentType() override;
};
