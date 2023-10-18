//
// Created by alexandre on 04/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "Vect2.hpp"

class Shooter : public GameEngine::AComponent {
public:
    Shooter(Utils::Vect2 shootPosition, Utils::Vect2 velocity, size_t typeBullet);

    size_t getComponentType() override;

    Utils::Vect2 shootPosition;
    Utils::Vect2 velocity;
    size_t typeBullet;
};
