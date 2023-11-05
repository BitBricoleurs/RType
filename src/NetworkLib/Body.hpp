//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <vector>
#include <cstdint>
#include "Pack.hpp"

namespace Network {
    class Body {
    public:
        Body() = default;
        ~Body() = default;

        void addData(std::vector<std::uint8_t> &data);
        std::vector<std::uint8_t> &getData();
        unsigned int getSize();
        void clear() { _data.clear(); }

    private:
        std::vector<std::uint8_t> _data = std::vector<std::uint8_t>();
    };
}
