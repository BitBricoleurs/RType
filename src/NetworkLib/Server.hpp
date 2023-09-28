//
// Created by Clément Lagasse on 28/09/2023.
//

#pragma once

#include <cstddef>
#include <memory>

namespace Network {
    class Server {
    public:
        Server(unsigned short port, size_t maxClients, size_t Tick);
        ~Server();

        void start();
        void stop();

    private:
        bool _isRunning;
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
}
