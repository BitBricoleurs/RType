//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <vector>

namespace Network {

    class IMessage {
    public:
        virtual ~IMessage() = default;

        virtual std::vector<std::uint8_t> &getMessage() = 0;
        virtual unsigned int getSize() = 0;
    };

    class Interface;
    struct OwnedMessage {
        std::shared_ptr<Network::Interface> remote;
        std::shared_ptr<IMessage> message;
    };
}
