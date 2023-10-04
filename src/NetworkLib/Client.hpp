//
// Created by Clément Lagasse on 28/09/2023.
//

#pragma once

#include <string>
#include <vector>
#include <any>
#include <memory>
#include <pthread.h>
#include "TSqueue.hpp"
#include "IMessage.hpp"

namespace Network {

    class Client {
    public:
        Client(std::size_t tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue);
        ~Client();

        void connect(const std::string &host, unsigned short port);
        void disconnect();
        bool isConnected() const;
        void send(const std::shared_ptr<IMessage>& message);

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };

}
