//
// Created by Clément Lagasse on 20/09/2023.
//

#pragma once

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <iostream>
#include <functional>
#include "Tick.hpp"
#include "IMessage.hpp"
#include "TSqueue.hpp"
#include "PacketComponent.hpp"
#include "Body.hpp"
#include "Message.hpp"

namespace Network {
    class Interface : public  std::enable_shared_from_this<Interface> {
    public:
        enum class Type {
            SERVER,
            CLIENT
        };

        Interface(asio::io_context &Context, TSQueue<OwnedMessage> &inMessages, Network::Tick &tick,
                  Network::Interface::Type type = Network::Interface::Type::CLIENT);

        ~Interface();

        bool isConnected();

        void disconnect();

        void connectToServer(const std::string &host, unsigned short port);

        void send(const std::shared_ptr<IMessage>& message);

        void processOutgoingMessages();

        asio::ip::udp::endpoint &getEndpoint();

        void processReceivedHeader(const PacketHeader& header, const std::function<void()>& callbackAfterRead);

    private:

        void readHeader();

        void readBody(const std::function<void()>& callbackAfterRead);


        void WriteHeader();

        void WriteBody();

            asio::io_context &_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _endpoint;
            asio::ip::udp::resolver _resolver;


            TSQueue<std::shared_ptr<IMessage> > _outMessages;
            TSQueue<OwnedMessage> &_inMessages;

            Network::PacketHeader _tempHeader;
            Network::Body _tempBody;

            unsigned int _id;

            Network::Interface::Type _type;

            Network::Tick &_tick;


    };
};
