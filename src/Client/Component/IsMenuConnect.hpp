//
// Created by Clément Lagasse on 24/10/2023.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    class IsMenuConnect : public GameEngine::AComponent {
    public:
      IsMenuConnect() = default;

      size_t getComponentType() override;
    };

}