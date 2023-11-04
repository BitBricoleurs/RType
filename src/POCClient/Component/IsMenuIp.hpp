//
// Created by Clément Lagasse on 24/10/2023.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    class IsMenuIp : public GameEngine::AComponent {
    public:
      IsMenuIp() = default;

      size_t getComponentType() override;
    };

}
