//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "ParallaxUtils.hpp"

namespace Server {

    class IsParallax : public GameEngine::AComponent {
    public:
      explicit IsParallax(float layer, bool isLooping, ParallaxType type);
      ~IsParallax() override = default;

      size_t getComponentType() override;
      float layer = 1;
      bool isLooping = false;
      ParallaxType type = ParallaxType::NONE;
    };

}
