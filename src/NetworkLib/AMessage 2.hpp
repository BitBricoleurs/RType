//
// Created by Clément Lagasse on 03/10/2023.
//

#pragma once

#include "IMessage.hpp"

namespace Network {
    class AMessage : public IMessage {
    public:
        AMessage() = default;
        AMessage(std::vector<std::uint8_t> &message) {
            _message = message;
        }
        ~AMessage() override = default;

        std::vector<std::uint8_t> &getMessage() override {
            return _message;
        }
        unsigned int getSize() override {
            return _message.size();
        }

    protected:
        std::vector<std::uint8_t> _message;
    };
};
