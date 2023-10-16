//
// Created by alexandre on 03/10/23.
//

#include "IsPowerUp.hpp"

IsPowerUp::IsPowerUp(size_t type) : type(type) {};

size_t IsPowerUp::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("IsPowerUp");
}
