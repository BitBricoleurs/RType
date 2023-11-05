//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    class IsParallax : public GameEngine::AComponent {
    public:
      IsParallax() = default;
      ~IsParallax() = default;

      size_t getComponentType() override;
    };

}