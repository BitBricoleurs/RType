//
// Created by Bartosz on 10/10/23.
//

#include "isPowerUpPickUp.hpp"

isPowerUpPickUp::isPowerUpPickUp(size_t powerUpType) {
    this->powerUpType = powerUpType;
}


size_t isPowerUpPickUp::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("isPowerUpPickUp");
}