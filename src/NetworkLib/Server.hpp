//
// Created by Clément Lagasse on 28/09/2023.
//

#pragma once

#include <cstddef>
#include <memory>
#include <any>
#include "TSqueue.hpp"
#include "IMessage.hpp"

namespace Network {
    class Server {
    public:
        Server(unsigned short port, size_t maxClients, size_t Tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue);
        ~Server();

        void start();
        void stop();

        void sendClient(unsigned int id, const std::shared_ptr<IMessage>& message);

        void sendAllClients(const std::shared_ptr<IMessage>& message);

        void sendAllClientsExcept(unsigned int id, const std::shared_ptr<IMessage>& message);

        void sendClients(const std::vector<unsigned int> &ids, const std::shared_ptr<IMessage>& message);

        void disconnectClient(unsigned int id);

        Network::TSQueue<unsigned int> &getConnectedClients();
        Network::TSQueue<unsigned int> &getDisconnectedClients();

    private:
        bool _isRunning;
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
}
