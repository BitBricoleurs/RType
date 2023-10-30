//
// Created by alexandre on 18/10/23.
//

#pragma once

namespace Utils {
    struct rect {
        float x, y, w, h;
        rect();
        rect(float x, float y, float w, float h);

        bool operator==(const rect &other) const;
        bool operator!=(const rect &other) const;
        rect operator+(const rect &other) const;
        rect& operator=(const rect &other);
    };
}
