//
// Created by Clément Lagasse on 05/10/2023.
//

#pragma once

#include "IMessage.hpp"

namespace Network {

    struct UserMessage {
        size_t id;
        std::shared_ptr<IMessage> message;
    };
    struct UsersMessage {
        std::vector<size_t> ids;
        std::shared_ptr<IMessage> message;
    };
    struct NotUserMessage {
        size_t id;
        std::shared_ptr<IMessage> message;
    };
};
