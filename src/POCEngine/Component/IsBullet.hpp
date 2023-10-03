//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>

class IsBullet : public GameEngine::AComponent {
public:
  IsBullet() = default;

  size_t getComponentType() override;
};
