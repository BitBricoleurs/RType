//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Server {

    class IsPowerUp : public GameEngine::AComponent {
    public:
      IsPowerUp() = default;

      size_t getComponentType() override;
    };
}
