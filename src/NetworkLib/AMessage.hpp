//
// Created by Clément Lagasse on 03/10/2023.
//

#pragma once

#include "IMessage.hpp"

namespace Network {
    class AMessage : public IMessage {
    public:
        AMessage(bool secure = false) {
            _message = std::vector<std::uint8_t>();
            this->_secure = secure;
        }
        AMessage(std::vector<std::uint8_t> &message) {
            _message = message;
        }
        AMessage(std::vector<std::uint8_t> &message, bool secure) {
            _message = message;
            this->_secure = secure;
        }
        ~AMessage() override = default;

        std::vector<std::uint8_t> &getMessage() override {
            return _message;
        }
        unsigned int getSize() override {
            return _message.size();
        }

        bool isMessageSecure() {return _secure;};
    protected:
        std::vector<std::uint8_t> _message;
        bool _secure = false;
    };
};
