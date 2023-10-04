//
// Created by alexandre on 04/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsForcePod : public GameEngine::AComponent {
public:
  IsForcePod() = default;

  size_t getComponentType() override;
};
