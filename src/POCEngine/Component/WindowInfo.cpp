//
// Created by alexandre on 05/10/23.
//

#include "WindowInfo.hpp"

WindowInfo::WindowInfo(size_t windowWidth, size_t windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight)
{}

size_t WindowInfo::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("WindowInfo");
}
