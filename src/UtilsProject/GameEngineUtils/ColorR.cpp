//
// Created by alexandre on 18/10/23.
//

#include "ColorR.hpp"

namespace Utils {
    ColorR::ColorR() : r(255), g(255), b(255), a(255) {}
    ColorR::ColorR(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : r(r), g(g), b(b), a(a) {}
}
