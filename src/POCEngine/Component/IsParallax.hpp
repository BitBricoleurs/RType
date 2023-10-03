//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsParallax : public GameEngine::AComponent {
public:
  IsParallax() = default;
  ~IsParallax() override = default;

  size_t getComponentType() override;

private:
};
