//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Server {

    class IsPlayer : public GameEngine::AComponent {
    public:
      explicit IsPlayer(size_t entityIdChargeAnimation);

      size_t getComponentType() override;
      size_t entityIdForcePod = 0;
      size_t entityIdChargeAnimation = 0;
      int PowerUp = 0;
    };
}
