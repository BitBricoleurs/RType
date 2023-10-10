//
// Created by Theophilus Homawoo on 04/10/2023.
//

#include "isHealthBar.hpp"

size_t isHealthBar::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("IsHealthBar");
}