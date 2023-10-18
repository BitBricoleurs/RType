//
// Created by alexandre on 18/10/23.
//

#pragma once
#include "Point.hpp"

namespace Utils {
    struct Circle {
        Point center;
        float radius;

        Circle();
        Circle(const Point &center, float radius);
    };
}
