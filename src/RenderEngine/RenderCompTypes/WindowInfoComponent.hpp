//
// Created by alexandre on 05/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace RenderEngine {

    class WindowInfoComponent : public GameEngine::AComponent {
    public:
      explicit WindowInfoComponent(size_t windowWidth, size_t windowHeight);

      size_t getComponentType() override;

      size_t windowWidth;
      size_t windowHeight;
    };

} // namespace RenderEngine