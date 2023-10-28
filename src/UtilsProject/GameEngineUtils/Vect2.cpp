//
// Created by alexandre on 18/10/23.
//

#include "Vect2.hpp"

namespace Utils {
    Vect2::Vect2() : x(0.0f), y(0.0f) {}
    Vect2::Vect2(float x, float y) : x(x), y(y) {}

    Vect2 Vect2::operator+(const Vect2& v) const {
        return Vect2(x + v.x, y + v.y);
    }

    Vect2 Vect2::operator-(const Vect2& v) const {
        return Vect2(x - v.x, y - v.y);
    }

    Vect2 Vect2::operator*(float scalar) const {
        return Vect2(x * scalar, y * scalar);
    }

    Vect2& Vect2::operator+=(const Vect2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vect2& Vect2::operator-=(const Vect2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vect2& Vect2::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    float Vect2::distanceTo(const Vect2& other) const {
            float dx = other.x - x;
            float dy = other.y - y;
            return std::sqrt(dx * dx + dy * dy);
        }

    float Vect2::magnitude() const { return std::sqrt(x * x + y * y); }

    Vect2 Vect2::normalize() const {
        float mag = magnitude();
        if (mag == 0) return { 0, 0 };
        return { x / mag, y / mag };
    }
}
