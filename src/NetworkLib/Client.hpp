//
// Created by Clément Lagasse on 28/09/2023.
//

#pragma once

#include <string>
#include <vector>
#include <any>
#include <memory>
#include <pthread.h>

namespace Network {

    class Client {
    public:
        Client(std::size_t tick);
        ~Client();

        void connect(const std::string &host, unsigned short port);
        void disconnect();
        bool isConnected() const;
        void send(const std::string &action, std::vector<unsigned int> IDs, const std::string &typeArg, std::vector<std::any> args);
        void send(const std::string &action, std::vector<unsigned int> IDs, const std::string &typeArg, std::any arg);

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };

}
