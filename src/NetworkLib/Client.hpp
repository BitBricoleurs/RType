#pragma once

#include <memory>
#include "TSqueue.hpp"
#include "IMessage.hpp"

namespace Network {
    class Client {
    public:
        static void init(std::size_t tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue);
        static Client& getInstance();

        void connect(const std::string &host, unsigned short port);
        void disconnect();
        bool isConnected() const;
        void send(const std::shared_ptr<IMessage>& message);

        ~Client();

    private:
        Client();
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
}
