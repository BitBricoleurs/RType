//
// Created by alexandre on 03/10/23.
//

#include "test/EntityComponents.hpp"
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include <cstddef>

#pragma once

class BulletStartPosition : public GameEngine::AComponent {
public:
  BulletStartPosition(float startX, float startY);

  size_t getComponentType() override;

  float startX, startY;
};
