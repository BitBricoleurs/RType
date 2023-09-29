//
// Created by Bartosz on 9/26/23.
//

#pragma once

namespace GameEngine {
    struct rect {
        float x;
        float y;
        float width;
        float height;
    };

    struct Vect2 {
        float x;
        float y;
    };

    struct Vect3 {
        float x;
        float y;
        float z;
    };

    struct ColorR {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
}