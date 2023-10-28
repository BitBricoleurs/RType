//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <utility>
#include <vector>
#include <cstdint>

namespace Network {

    class IMessage {
    public:
        virtual ~IMessage() = default;

        virtual std::vector<std::uint8_t> &getMessage() = 0;
        virtual unsigned int getSize() = 0;
        virtual bool isSecure() = 0;
    };

    class Message;
    struct OwnedMessage {
        OwnedMessage(unsigned int remote, std::shared_ptr<Network::IMessage> message) : remote(remote), message(std::move(message)) {}
        OwnedMessage(const OwnedMessage& other) = default;
        OwnedMessage(OwnedMessage&& other) noexcept : remote(other.remote), message(std::move(other.message)) {}
        OwnedMessage& operator=(const OwnedMessage& other) {
            remote = other.remote;
            message = other.message;
            return *this;
        }
        OwnedMessage& operator=(OwnedMessage&& other) noexcept {
            remote = other.remote;
            message = std::move(other.message);
            return *this;
        }
        unsigned int remote;
        std::shared_ptr<Network::IMessage> message;
    };
}
