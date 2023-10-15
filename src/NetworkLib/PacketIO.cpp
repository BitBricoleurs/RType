//
// Created by Clément Lagasse on 29/09/2023.
//

#include <iostream>
#include <utility>
#include "PacketIO.hpp"

Network::PacketIO::PacketIO(boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn, boost::asio::ip::udp::socket& socketOut, TSQueue<std::shared_ptr<Network::OwnedMessage>>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> & forwardMessages,Network::Tick& tick)
: _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _outMessages(&outMessages), _inMessages(inMessages),_tick(tick), _headerIn(), _headerOut(), _bodyOut(), _bodyIn(), _socketMutex(), _packetIn(), _packetOut(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _type(Type::CLIENT), _clients(nullptr), _forwardMessages(&forwardMessages), _currentSequenceNumber(0), _lastSequenceNumber(-1), _tempEndpoint()
{
    _headerIn.bodySize = 0;
    _headerOut.bodySize = 0;
}

Network::PacketIO::PacketIO(boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn, boost::asio::ip::udp::socket& socketOut, TSQueue<std::shared_ptr<Network::OwnedMessage>>& inMessages, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>& forwardMessages, Network::Tick& tick, std::function<void(boost::asio::ip::udp::endpoint &endpoint)> onConnect, std::vector<std::shared_ptr<Network::Interface> > &clients)
    : _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _inMessages(inMessages),_tick(tick), _headerIn(), _headerOut(), _bodyOut(), _bodyIn(), _socketMutex(), _packetIn(), _packetOut(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _onConnect(std::move(onConnect)), _type(Type::SERVER), _outMessages(nullptr), _clients(&clients), _forwardMessages(&forwardMessages), _currentSequenceNumber(0), _lastSequenceNumber(-1), _tempEndpoint()
{
    _headerIn.bodySize = 0;
    _headerOut.bodySize = 0;
}

void Network::PacketIO::readPacket()
{
    _socketIn.async_receive_from(
        boost::asio::buffer(_tempBuffer), _tempEndpoint,
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                Network::Packet receivedPacket;
                if (_type == Type::SERVER) {
                    _endpoint = _tempEndpoint;
                }
                memcpy(&receivedPacket.header, _tempBuffer.data(), sizeof(PacketHeader));
                _lastSequenceNumber = receivedPacket.header.sequenceNumber;
                receivedPacket.body.assign(_tempBuffer.begin() + sizeof(PacketHeader), _tempBuffer.begin() + length);
                _packetQueue.pushBack(receivedPacket);
            } else {
                std::cout << "Error reading packet: " << ec.message() << std::endl;
            }
            readPacket();
        });
}


void Network::PacketIO::serializePacket()
{
    _serializedPacket.resize(sizeof(PacketHeader) + _packetOut.body.size());
    memcpy(_serializedPacket.data(), &_packetOut.header, sizeof(PacketHeader));
    memcpy(_serializedPacket.data() + sizeof(PacketHeader), _packetOut.body.data(), _packetOut.body.size());
}

void Network::PacketIO::writePacket()
{
    serializePacket();
    _socketOut.async_send_to(
        boost::asio::buffer(_serializedPacket.data(), _serializedPacket.size()), _endpoint,
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                _tick.updateLastWriteTime();
            } else {
                std::cout << "Error writing packet" << ec.message()
                          << std::endl;
            }
        });
}

void Network::PacketIO::processIncomingMessages() {
    boost::asio::post(_context, [this]() {
        while (!_packetQueue.empty()) {
            Network::Packet rawData = _packetQueue.getFront();
            _packetQueue.popFront();

            _headerIn = rawData.header;
            _bodyIn.clear();
            _bodyIn.getData().assign(rawData.body.begin(), rawData.body.end());

            if (_type == Type::SERVER) {
                _onConnect(_endpoint);
            }

            size_t index = 0;
            unsigned int id = 0;
            std::uint16_t size;
            while (index < _headerIn.bodySize) {
                memcpy(&size, _bodyIn.getData().data() + index, sizeof(uint16_t));
                size = ntohs(size);
                std::vector<std::uint8_t> subData(_bodyIn.getData().begin() + index, _bodyIn.getData().begin() + index + size + sizeof(uint16_t));
                std::shared_ptr<Network::IMessage> message = std::make_shared<Network::AMessage>(subData);
                id = EndpointGetter::getIdByEndpoint(_endpoint, _clients);
                std::shared_ptr<Network::OwnedMessage> ownedMessage = std::make_shared<Network::OwnedMessage>(id, message);
                _inMessages.pushBack(ownedMessage);
                index += size + sizeof(uint16_t);
            }

        }

        while (!_inMessages.empty()) {
            std::shared_ptr<OwnedMessage> message = _inMessages.getFront();
            _forwardMessages->pushBack(message);
            _inMessages.popFront();
        }
    });
}


void Network::PacketIO::processOutgoingMessages()
{
    boost::asio::post(_context, [this]() {
            uint16_t size = 0;
            if (!_outMessages || _outMessages->empty()) {
                return;
            }
            _bodyOut.clear();
            while (!_outMessages->empty()) {
                std::shared_ptr<IMessage> message= _outMessages->getFront();
                if (size + message->getSize() > MAX_PACKET_SIZE)
                    break;
                _outMessages->popFront();
                _bodyOut.addData( message->getMessage() );
                size+= message->getSize();
            }
            _packetOut.header.bodySize= size;
            _packetOut.header.sequenceNumber= _currentSequenceNumber++;
            _packetOut.header.ackMask= 0;
            _packetOut.header.lastPacketSeq = _lastSequenceNumber;
            _packetOut.body= _bodyOut.getData();
            if (_packetOut.header.bodySize > 0)
                writePacket();
    });
}

size_t Network::PacketIO::getOutMessagesSize() const
{
    return _outMessages->count();
}