//
// Created by alexandre on 04/10/23.
//

#include "Shooter.hpp"

namespace Server {

    size_t Shooter::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("Shooter");
    }
    Shooter::Shooter(Utils::Vect2 shootPosition, Utils::Vect2 velocity , size_t typeBullet) : shootPosition(shootPosition), typeBullet(typeBullet), velocity(velocity)
    {

    }
}
