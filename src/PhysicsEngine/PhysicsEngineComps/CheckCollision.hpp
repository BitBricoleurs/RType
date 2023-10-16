//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "Utils.hpp"
#include <algorithm>

class classCheckCollision {
    public:
    classCheckCollision() = default;
    ~classCheckCollision() = default;

    static bool checkCollision(const GameEngine::Circle& a, const GameEngine::Circle& b);
    static bool checkCollision(const GameEngine::rect& r, const GameEngine::Circle& c);
    static bool checkCollision(const GameEngine::rect& a, const GameEngine::rect& b);
};
