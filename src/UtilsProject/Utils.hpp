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
    };

    struct Vector3 {
        float x, y, z;
        Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    };
}