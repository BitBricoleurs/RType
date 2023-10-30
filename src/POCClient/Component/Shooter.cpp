//
// Created by alexandre on 04/10/23.
//

#include "Shooter.hpp"

namespace Client {

    size_t Shooter::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("Shooter");
    }

    Shooter::Shooter(Utils::Vect2 shootPosition, size_t typeBullet) : shootPosition(shootPosition), typeBullet(typeBullet)
    {

    }

}
