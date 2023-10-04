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

        Interface(boost::asio::io_context &Context, TSQueue<std::shared_ptr<OwnedMessage>> &inMessages, std::optional<std::reference_wrapper<boost::asio::ip::udp::socket>> _inSocket,
                  Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardMessages, Network::Tick &tick, unsigned int id, Network::Interface::Type type = Network::Interface::Type::CLIENT);

        ~Interface();

        bool isConnected();

        void disconnect();

        void connectToServer(const std::string &host, unsigned short port);

        void send(const std::shared_ptr<IMessage>& message);


        boost::asio::ip::udp::endpoint &getEndpoint();
        void setEndpoint(const boost::asio::ip::udp::endpoint &endpoint);
        std::shared_ptr<Network::PacketIO> getIO();
        unsigned int getId() const;


    private:

            boost::asio::io_context &_context;
            boost::asio::ip::udp::socket _socket;
            std::mutex _socketMutex;
            boost::asio::ip::udp::endpoint _endpoint;
            boost::asio::ip::udp::resolver _resolver;


            TSQueue<std::shared_ptr<IMessage> > _outMessages;

            unsigned int _id;

            Network::Interface::Type _type;

            Network::Tick &_tick;
            std::shared_ptr<Network::PacketIO> _packetIO;

    };
};
