//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Server {

    class IsMob : public GameEngine::AComponent {
    public:
      IsMob() = default;

      size_t getComponentType() override;
    };
}
