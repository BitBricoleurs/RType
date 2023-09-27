//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <vector>
#include <cstdint>

namespace Network {
    class Body {
    public:
        Body() = default;
        ~Body() = default;

        void addData(std::vector<std::uint8_t> &data) {
            this->_data.insert(this->_data.end(), data.begin(), data.end());
        }

        std::vector<std::uint8_t> &getData() {
            return this->_data;
        }

        unsigned int getSize() {
            return this->_data.size();
        }
    private:
        std::vector<std::uint8_t> _data;
    } __attribute__((packed));
}
