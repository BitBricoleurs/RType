//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsPlayer : public GameEngine::AComponent {
public:
  IsPlayer() = default;

  size_t getComponentType() override;
};
