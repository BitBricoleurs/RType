//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include <string>

namespace Network {
    struct Endpoint {
        std::string ip;
        unsigned short port;
    };
}