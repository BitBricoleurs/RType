//
// Created by Clément Lagasse on 25/10/2023.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    class IsMenuPort : public GameEngine::AComponent {
    public:
      IsMenuPort() = default;

      size_t getComponentType() override;
    };

}
