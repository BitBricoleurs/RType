//
// Created by Clément Lagasse on 28/09/2023.
//

#pragma once

#include <cstddef>
#include <memory>
#include <any>
#include "IMessage.hpp"

namespace Network {
    class Server {
    public:
        Server(unsigned short port, size_t maxClients, size_t Tick);
        ~Server();

        void start();
        void stop();

        void sendClient(unsigned int id, const std::string &action, std::vector<unsigned int> IDs, const std::string &typeArg, std::vector<std::any> args);
        void sendClient(unsigned int id, const std::shared_ptr<IMessage>& message);

        void sendAllClients(const std::string &action, std::vector<unsigned int> IDs, const std::string &typeArg, std::vector<std::any> args);
        void sendAllClients(const std::shared_ptr<IMessage>& message);

        void sendAllClientsExcept(unsigned int id, const std::string &action, std::vector<unsigned int> IDs, const std::string &typeArg, std::vector<std::any> args);
        void sendAllClientsExcept(unsigned int id, const std::shared_ptr<IMessage>& message);

    private:
        bool _isRunning;
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
}
