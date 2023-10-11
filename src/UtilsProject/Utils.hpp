//
// Created by Bartosz on 9/26/23.
//

#pragma once
#include <cmath>

namespace GameEngine {
    struct rect {
        float x, y, w, h;
        rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}
        rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
    };

    struct Vect2 {
        float x, y;

        Vect2() : x(0.0f), y(0.0f) {}
        Vect2(float x, float y) : x(x), y(y) {}

        Vect2 operator+(const Vect2& v) const {
            return Vect2(x + v.x, y + v.y);
        }

        Vect2 operator-(const Vect2& v) const {
            return Vect2(x - v.x, y - v.y);
        }

        Vect2 operator*(float scalar) const {
            return Vect2(x * scalar, y * scalar);
        }

        Vect2& operator+=(const Vect2& v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vect2& operator-=(const Vect2& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vect2& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        float magnitude() const { return std::sqrt(x * x + y * y); }

        // Normalize the vector and return it
        Vect2 normalize() const {
          float mag = magnitude();
          // To handle the case where magnitude is zero (avoid division by zero)
          if (mag == 0) {
            return Vect2(0, 0);
          }
          return Vect2(x / mag, y / mag);
        }
    };

    struct Vect3 {
        float x, y, z;
        Vect3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vect3(float x, float y, float z) : x(x), y(y), z(z) {}
    };

    struct Point {
        float x, y;

        Point() : x(0), y(0) {}
        Point(float x, float y) : x(x), y(y) {}
    };

    struct Circle {
        Point center;
        float radius;

        Circle() : center(), radius(0) {}

        Circle(const Point &center, float radius) : center(center), radius(radius) {}
    };
    struct ColorR {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
}
