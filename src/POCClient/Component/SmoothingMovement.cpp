//
// Created by Clément Lagasse on 27/10/2023.
//

#include "SmoothingMovement.hpp"

size_t Client::SmoothingMovement::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("SmoothingMovement");
}
