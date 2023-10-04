//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsParallaxComponent : public GameEngine::AComponent {
public:
  IsParallaxComponent() = default;
  ~IsParallaxComponent() = default;

  size_t getComponentType() override {
    return GameEngine::ComponentsType::getNewComponentType("IsParallaxComponent");
  }
};

