//
// Created by Clément Lagasse on 05/10/2023.
//

#pragma once

#include <memory>
#include "IMessage.hpp"

namespace Network {

    struct UserMessage {
        size_t id;
        std::shared_ptr<IMessage> message;
        UserMessage(size_t id, std::shared_ptr<IMessage> message) : id(id), message(message) {};
    };
    struct UsersMessage {
        std::vector<size_t> ids;
        std::shared_ptr<IMessage> message;
        UsersMessage(std::vector<size_t> ids, std::shared_ptr<IMessage> message) : ids(ids), message(message) {};
    };
    struct NotUserMessage {
        size_t id;
        std::shared_ptr<IMessage> message;
        NotUserMessage(size_t id, std::shared_ptr<IMessage> message) : id(id), message(message) {};
    };
    struct AllUsersMessage {
        std::shared_ptr<IMessage> message;
        AllUsersMessage(std::shared_ptr<IMessage> message) : message(message) {};
    };
};
