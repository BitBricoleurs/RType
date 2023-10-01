//
// Created by Clément Lagasse on 20/09/2023.
//

#pragma once

#include "PacketIO.hpp"

namespace Network {
    class Interface {
    public:
        enum class Type {
            SERVER,
            CLIENT
        };

        Interface(asio::io_context &Context, TSQueue<OwnedMessage> &inMessages, std::optional<std::reference_wrapper<asio::ip::udp::socket>> _inSocket,
                   Network::Tick &tick, unsigned int id, Network::Interface::Type type = Network::Interface::Type::CLIENT);

        ~Interface();

        bool isConnected();

        void disconnect();

        void connectToServer(const std::string &host, unsigned short port);

        void send(const std::shared_ptr<IMessage>& message);


        asio::ip::udp::endpoint &getEndpoint();
        void setEndpoint(const asio::ip::udp::endpoint &endpoint);
        std::shared_ptr<Network::PacketIO> getIO();
        unsigned int getId() const;


    private:

            asio::io_context &_context;
            asio::ip::udp::socket _socket;
            std::mutex _socketMutex;
            asio::ip::udp::endpoint _endpoint;
            asio::ip::udp::resolver _resolver;


            TSQueue<std::shared_ptr<IMessage> > _outMessages;

            unsigned int _id;

            Network::Interface::Type _type;

            Network::Tick &_tick;
            std::shared_ptr<Network::PacketIO> _packetIO;

    };
};
