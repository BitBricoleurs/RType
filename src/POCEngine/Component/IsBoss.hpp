//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>

class IsBoss : public GameEngine::AComponent {
public:
  IsBoss() = default;

  size_t getComponentType() override;
};
