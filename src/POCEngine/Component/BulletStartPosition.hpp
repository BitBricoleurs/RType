//
// Created by alexandre on 03/10/23.
//

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

#pragma once

class BulletStartPosition : public GameEngine::AComponent {
public:
  BulletStartPosition(float startX, float startY);

  size_t getComponentType() override;

  float startX, startY;
};
