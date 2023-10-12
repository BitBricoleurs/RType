//
// Created by alexandre on 12/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsStaships : public GameEngine::AComponent {
public:
  IsStaships() = default;

  size_t getComponentType() override;
};
