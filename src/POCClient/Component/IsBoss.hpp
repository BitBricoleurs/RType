//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    class IsBoss : public GameEngine::AComponent {
    public:
      IsBoss() = default;

      size_t getComponentType() override;
    };

}
