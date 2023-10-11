//
// Created by Bartosz on 10/10/23.
//

#include "isPowerUpPickUp.hpp"

size_t isPowerUpPickUp::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("isPowerUpPickUp");
}