//
// Created by alexandre on 12/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

class IsStarship : public GameEngine::AComponent {
public:
  explicit IsStarship(size_t entityIdChargeAnimation);

  size_t getComponentType() override;

   size_t entityIdChargeAnimation;
};
