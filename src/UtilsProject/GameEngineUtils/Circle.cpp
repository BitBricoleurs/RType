//
// Created by alexandre on 18/10/23.
//

#include "Circle.hpp"

namespace Utils {
    Circle::Circle() : center(), radius(0) {}
    Circle::Circle(const Point &center, float radius) : center(center), radius(radius) {}
}
