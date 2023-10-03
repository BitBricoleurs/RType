//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Utils.hpp"

namespace GameEngine {
class VelocityComponent : public AComponent {
public:
  VelocityComponent() = default;
  VelocityComponent(const Vect2 &velocity) : velocity(velocity) {}
  ~VelocityComponent() override = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("VelocityComponent");
  }
  Vect2 getVelocity() const { return velocity; }
  void setVelocity(const Vect2 &velocity) { this->velocity = velocity; }
  Vect2 velocity;
};
} // namespace GameEngine