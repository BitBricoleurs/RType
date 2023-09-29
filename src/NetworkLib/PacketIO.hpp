//
// Created by Clément Lagasse on 29/09/2023.
//

#pragma once

#include <memory>
#include <functional>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "PacketComponent.hpp"
#include "Body.hpp"
#include "IMessage.hpp"
#include "TSqueue.hpp"
#include "Message.hpp"
#include "Tick.hpp"

namespace Network {
    class PacketIO : public std::enable_shared_from_this<PacketIO>{
      public:
        PacketIO( asio::io_context& context, asio::ip::udp::endpoint& endpoint, asio::ip::udp::socket& socketIn,
                  asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages,
                  Network::Tick& tick, const std::optional<std::function<void()>>& callbackFunction);

        ~PacketIO() = default;

        void setHeader( const Network::PacketHeader& header );
        void setBody( const Network::Body& body );

        void readHeader();
        void readBody();

        void writePacket();

        void processOutgoingMessages();

      private:

        TSQueue<std::shared_ptr<IMessage>> &_outMessages;
        Network::TSQueue<Network::OwnedMessage> &_inMessages;
        Network::Tick& _tick;
        asio::io_context& _context;
        asio::ip::udp::endpoint& _endpoint;

        asio::ip::udp::socket& _socketIn;
        asio::ip::udp::socket& _socketOut;

        Network::PacketHeader _header;
        Network::Body _body;
        Network::Packet _packet;
        std::mutex _socketMutex;

        std::function<void()> _callbackListen;

    };
}