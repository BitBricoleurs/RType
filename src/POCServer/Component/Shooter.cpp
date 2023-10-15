//
// Created by alexandre on 04/10/23.
//

#include "Shooter.hpp"

size_t Shooter::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("Shooter");
}
Shooter::Shooter(GameEngine::Vect2 shootPosition, GameEngine::Vect2 velocity , size_t typeBullet) : shootPosition(shootPosition), typeBullet(typeBullet), velocity(velocity)
{

}
