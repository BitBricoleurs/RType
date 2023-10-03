//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <vector>
#include <cstdint>

namespace Network {

    class IMessage {
    public:
        virtual ~IMessage() = default;

        virtual std::vector<std::uint8_t> &getMessage() = 0;
        virtual unsigned int getSize() = 0;
    };

    class Message;
    struct OwnedMessage {
        unsigned int remote;
        std::shared_ptr<Network::Message> message;
    };
}