#pragma once

#include <cstddef>
#include <memory>
#include <any>
#include "TSqueue.hpp"
#include "IMessage.hpp"

namespace Network {
    class Server {
    public:
        static void init(unsigned short port, size_t maxClients, size_t Tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue);
        static Server& getInstance();

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
        Server();
        ~Server();

        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        bool _isRunning;
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
}
