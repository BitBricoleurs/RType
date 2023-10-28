//
// Created by alexandre on 18/10/23.
//

#include "rect.hpp"

namespace Utils {
    rect::rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}
    rect::rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}


    bool rect::operator==(const rect &other) const {
        return x == other.x && y == other.y && w == other.w && h == other.h;
    }

    bool rect::operator!=(const rect &other) const {
        return !(*this == other);
    }

    rect rect::operator+(const rect &other) const {
        return rect(x + other.x, y + other.y, w + other.w, h + other.h);
    }

    rect& rect::operator=(const rect &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            w = other.w;
            h = other.h;
        }
        return *this;
    }

}
