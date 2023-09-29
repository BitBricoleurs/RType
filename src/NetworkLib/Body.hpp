//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#pragma pack(1)

#include <vector>
#include <cstdint>

namespace Network {
    class Body {
    public:
        Body() = default;
        ~Body() = default;

        void addData(std::vector<std::uint8_t> &data);
        std::vector<std::uint8_t> &getData();
        unsigned int getSize();

    private:
        std::vector<std::uint8_t> _data;
    } __attribute__((packed));
}
