//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include <string>

namespace Network {
    struct Endpoint {
        Endpoint(const std::string &ip, unsigned short port) : ip(ip), port(port) {};
        std::string ip;
        unsigned short port;
    };
}