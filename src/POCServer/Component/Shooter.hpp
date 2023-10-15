//
// Created by alexandre on 04/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "Utils.hpp"

class Shooter : public GameEngine::AComponent {
public:
    Shooter(GameEngine::Vect2 shootPosition, GameEngine::Vect2 velocity, size_t typeBullet);

    size_t getComponentType() override;

    GameEngine::Vect2 shootPosition;
    GameEngine::Vect2 velocity;
    size_t typeBullet;
};
