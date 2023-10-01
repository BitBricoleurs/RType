//
// Created by Clément Lagasse on 29/09/2023.
//

#pragma once

#include <memory>
#include <functional>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <asio/buffer.hpp>
#include "PacketComponent.hpp"
#include "Body.hpp"
#include "IMessage.hpp"
#include "TSqueue.hpp"
#include "Message.hpp"
#include "Tick.hpp"
#include "EndpointGetter.hpp"

namespace Network {

    class Interface;

    class PacketIO : public std::enable_shared_from_this<PacketIO>{
      public:
        enum class Type {
            SERVER,
            CLIENT
        };
        PacketIO( asio::io_context& context, asio::ip::udp::endpoint& endpoint, asio::ip::udp::socket& socketIn,
                  asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages,
                  Network::Tick& tick);

        PacketIO( asio::io_context& context, asio::ip::udp::endpoint& endpoint, asio::ip::udp::socket& socketIn,
                  asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages,
                  Network::Tick& tick, std::function<void(asio::ip::udp::endpoint &endpoint)>, std::vector<std::shared_ptr<Network::Interface> > &client);

        ~PacketIO() = default;

        void setHeader( const Network::PacketHeader& header );
        void setBody( const Network::Body& body );

        void readPacket();

        void writePacket();

        void processOutgoingMessages();

      private:

        unsigned int getIdByEndpoint(const asio::ip::udp::endpoint& endpoint);
        asio::ip::udp::endpoint getEndpointById(unsigned int id);

        void serializePacket();

        TSQueue<std::shared_ptr<IMessage>>* _outMessages;
        Network::TSQueue<Network::OwnedMessage> &_inMessages;
        Network::Tick& _tick;
        asio::io_context& _context;
        asio::ip::udp::endpoint& _endpoint;

        asio::ip::udp::socket& _socketIn;
        asio::ip::udp::socket& _socketOut;

        Network::PacketHeader _header;
        Network::Body _body;
        Network::Packet _packet;
        std::vector<unsigned char> _serializedPacket;
        std::mutex _socketMutex;

        std::vector<std::uint8_t> _tempBuffer;

        std::function<void(asio::ip::udp::endpoint &endpoint)> _onConnect;
        Network::PacketIO::Type _type;

        std::vector<std::shared_ptr<Network::Interface>>* _clients;
    };
}