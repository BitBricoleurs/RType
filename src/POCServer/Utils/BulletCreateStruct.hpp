//
// Created by Clément Lagasse on 10/10/2023.
//

#pragma once

#include "Utils.hpp"

struct BulletCreate {

    BulletCreate(GameEngine::Vect2 &position, GameEngine::Vect2 &velocity, bool isBulletPlayer, bool isBulletCharged)
    : position(position), velocity(velocity), isBulletPlayer(isBulletPlayer), isBullletCharged(isBulletCharged) {}

    BulletCreate() = default;
    GameEngine::Vect2 position;
    GameEngine::Vect2 velocity;
    bool isBulletPlayer;
    bool isBullletCharged;
};
