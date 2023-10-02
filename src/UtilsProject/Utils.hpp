//
// Created by Bartosz on 9/26/23.
//

#pragma once

namespace GameEngine {
    struct rect {
        float x, y, w, h;
        rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}
        rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
    };

    struct Vector2 {
        float x, y;

        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float x, float y) : x(x), y(y) {}

        Vector2 operator+(const Vector2& v) const {
            return Vector2(x + v.x, y + v.y);
        }

        Vector2 operator-(const Vector2& v) const {
            return Vector2(x - v.x, y - v.y);
        }

        Vector2 operator*(float scalar) const {
            return Vector2(x * scalar, y * scalar);
        }

        Vector2& operator+=(const Vector2& v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
    };

    struct Vector3 {
        float x, y, z;
        Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
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