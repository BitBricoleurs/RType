//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>

class IsParallax : public GameEngine::AComponent {
public:
  IsParallax() = default;
  ~IsParallax() override = default;

  size_t getComponentType() override;

private:
};
