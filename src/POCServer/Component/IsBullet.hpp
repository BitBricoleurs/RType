//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "vector"

class IsBullet : public GameEngine::AComponent {
public:
  IsBullet(bool playerBullet);

  size_t getComponentType() override;
  bool playerBullet = false;
  bool passingThrough = false;
  std::vector<size_t> alreadyHit;
};
