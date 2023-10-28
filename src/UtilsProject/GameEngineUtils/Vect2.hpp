//
// Created by alexandre on 18/10/23.
//

#pragma once
#include <cmath>

namespace Utils {
    struct Vect2 {
        float x, y;

        Vect2();
        Vect2(float x, float y);

        Vect2 operator+(const Vect2& v) const;
        Vect2 operator-(const Vect2& v) const;
        Vect2 operator*(float scalar) const;

        Vect2& operator+=(const Vect2& v);
        Vect2& operator-=(const Vect2& v);
        Vect2& operator*=(float scalar);

        float magnitude() const;
        Vect2 normalize() const;
    };
}
