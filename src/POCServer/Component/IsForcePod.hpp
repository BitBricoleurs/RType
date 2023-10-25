//
// Created by alexandre on 04/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Server {

    class IsForcePod : public GameEngine::AComponent {
    public:
      IsForcePod();

      size_t getComponentType() override;

      size_t entityId;
    };
}
