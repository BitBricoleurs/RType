//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "PowerUpUtils.hpp"

namespace Server {

    class IsPower : public GameEngine::AComponent {
    public:
      explicit IsPower(PowerUpType type);

      size_t getComponentType() override;
      PowerUpType type;
    };
}
