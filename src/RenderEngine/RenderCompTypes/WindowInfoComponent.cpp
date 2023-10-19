//
// Created by alexandre on 05/10/23.
//

#include "WindowInfoComponent.hpp"

namespace RenderEngine {

    WindowInfoComponent::WindowInfoComponent(size_t windowWidth, size_t windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
    {}

    size_t WindowInfoComponent::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("WindowInfoComponent");
    }

}
