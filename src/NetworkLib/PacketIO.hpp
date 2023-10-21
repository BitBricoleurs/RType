//
// Created by Clément Lagasse on 29/09/2023.
//

#pragma once

#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/asio/buffer.hpp>
#include "PacketComponent.hpp"
#include "Body.hpp"
#include "IMessage.hpp"
#include "TSqueue.hpp"
#include "AMessage.hpp"
#include "Tick.hpp"
#include "EndpointGetter.hpp"
#include "PacketRegister.hpp"

namespace Network {

    class Interface;

    class PacketIO : public std::enable_shared_from_this<PacketIO>{
      public:
        enum class Type {
            SERVER,
            CLIENT
        };
        PacketIO( boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn,
                  boost::asio::ip::udp::socket& socketOut, TSQueue<std::shared_ptr<Network::OwnedMessage>>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>& forwardMessages,
                  Network::Tick& tick, Network::PacketRegister &registerPacket);

        PacketIO( boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn,
                  boost::asio::ip::udp::socket& socketOut, TSQueue<std::shared_ptr<Network::OwnedMessage>>& inMessages, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>& forwardMessages,
                  Network::Tick& tick, std::function<void(boost::asio::ip::udp::endpoint &endpoint)>, std::vector<std::shared_ptr<Network::Interface> > &client, Network::PacketRegister &registerPacket);

        ~PacketIO() = default;

        void readPacket();

        void writePacket();

        void processOutgoingMessages();
        void processIncomingMessages();

        void fillResendQueue(boost::asio::ip::udp::endpoint &endpoint);
        void resendPacket();

        size_t getOutMessagesSize() const;

      private:

        unsigned int getIdByEndpoint(const boost::asio::ip::udp::endpoint& endpoint);
        boost::asio::ip::udp::endpoint getEndpointById(unsigned int id);

        void serializePacket();

        TSQueue<std::shared_ptr<IMessage>>* _outMessages;
        Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>* _forwardMessages;
        Network::TSQueue<std::pair<boost::asio::ip::udp::endpoint, Network::Packet>> _packetQueue;
        Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &_inMessages;
        Network::Tick& _tick;
        boost::asio::io_context& _context;
        boost::asio::ip::udp::endpoint& _endpoint;
        boost::asio::ip::udp::endpoint _tempEndpoint;

        boost::asio::ip::udp::socket& _socketIn;
        boost::asio::ip::udp::socket& _socketOut;

        Network::PacketHeader _headerIn;
        Network::Body _bodyIn;
        Network::Packet _packetIn;

        Network::PacketHeader _headerOut;
        Network::Body _bodyOut;
        Network::Packet _packetOut;

        std::vector<unsigned char> _serializedPacket;
        std::mutex _socketMutex;

        std::vector<std::uint8_t> _tempBuffer;

        std::function<void(boost::asio::ip::udp::endpoint &endpoint)> _onConnect;
        Network::PacketIO::Type _type;

        std::vector<std::shared_ptr<Network::Interface>>* _clients;
        int _currentSequenceNumber;
        long _id;
        Network::PacketRegister &_registerPacket;
        Network::TSQueue<std::pair<boost::asio::ip::udp::endpoint&, Network::Packet>> _resendQueue;
    };
}