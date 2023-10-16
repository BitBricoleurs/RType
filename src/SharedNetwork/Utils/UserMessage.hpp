//
// Created by Clément Lagasse on 05/10/2023.
//

#pragma once

#include <memory>
#include "Message.hpp"

namespace Network {

    struct UserMessage {
        unsigned int id;
        std::shared_ptr<IMessage> message;
        UserMessage(unsigned int id, std::shared_ptr<IMessage> message) : id(id), message(message) {};
    };
    struct UsersMessage {
        std::vector<unsigned int> ids;
        std::shared_ptr<IMessage> message;
        UsersMessage(std::vector<unsigned int> ids, std::shared_ptr<IMessage> message) : ids(ids), message(message) {};
    };
    struct NotUserMessage {
        unsigned int id;
        std::shared_ptr<IMessage> message;
        NotUserMessage(unsigned int id, std::shared_ptr<IMessage> message) : id(id), message(message) {};
    };
    struct AllUsersMessage {
        std::shared_ptr<IMessage> message;
        AllUsersMessage(std::shared_ptr<IMessage> message) : message(message) {};
    };
};
