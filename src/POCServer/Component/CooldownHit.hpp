//
// Created by clagasse on 10/31/23.
//
#include <cstddef>
#include <chrono>
#include "AComponent.hpp"
#include "ComponentsType.hpp"

#pragma once

namespace Server {

    class CooldownHit : public GameEngine::AComponent {
    public:
      CooldownHit();

      size_t getComponentType() override;

      std::chrono::time_point<std::chrono::system_clock> lastHit;
    };
}
