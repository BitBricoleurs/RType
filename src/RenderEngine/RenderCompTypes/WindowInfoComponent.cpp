//
// Created by alexandre on 05/10/23.
//

#include "WindowInfoComponent.hpp"

namespace RenderEngine {

    WindowInfoComponent::WindowInfoComponent(size_t windowWidth, size_t windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
    {
        camera = {0};
        camera.offset = {windowHeight / 2.0f, windowWidth / 2.0f};
        camera.target = {windowHeight / 2.0f, windowWidth / 2.0f};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    }

    size_t WindowInfoComponent::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("WindowInfoComponent");
    }

}
