//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include <vector>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsBullet : public GameEngine::AComponent {
public:
  IsBullet(bool playerBullet);

  size_t getComponentType() override;
  bool playerBullet;
  bool passingThrough;
  std::vector<size_t> alreadyHit;
};
