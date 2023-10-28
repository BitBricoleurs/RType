//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "Circle.hpp"
#include "rect.hpp"
#include <algorithm>

namespace PhysicsEngine {

    class classCheckCollision {
        public:
        classCheckCollision() = default;
        ~classCheckCollision() = default;

        static bool checkCollision(const Utils::Circle& a, const Utils::Circle& b);
        static bool checkCollision(const Utils::rect& r, const Utils::Circle& c);
        static bool checkCollision(const Utils::rect& a, const Utils::rect& b);
    };

}
