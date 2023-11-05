//
// Created by Clément Lagasse on 29/09/2023.
//

#include <iostream>
#include <utility>
#include "PacketIO.hpp"

Network::PacketIO::PacketIO(boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn, boost::asio::ip::udp::socket& socketOut, TSQueue<std::shared_ptr<Network::OwnedMessage>>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> & forwardMessages,Network::Tick& tick, Network::PacketRegister &registerPacket, std::function<void(unsigned int)> onReceivePacket)
: _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _outMessages(&outMessages), _inMessages(inMessages),_tick(tick), _headerIn(), _headerOut(), _bodyOut(), _bodyIn(), _socketMutex(), _packetIn(), _packetOut(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _type(Type::CLIENT), _clients(nullptr), _forwardMessages(&forwardMessages), _currentSequenceNumber(0), _tempEndpoint(), _registerPacket(registerPacket), _onReceivePacket(std::move(onReceivePacket))
{
    _headerIn.bodySize = 0;
    _id = -1;
    _headerOut.bodySize = 0;
}

Network::PacketIO::PacketIO(boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn, boost::asio::ip::udp::socket& socketOut, TSQueue<std::shared_ptr<Network::OwnedMessage>>& inMessages, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>& forwardMessages, Network::Tick& tick, std::function<void(boost::asio::ip::udp::endpoint &endpoint)> onConnect, std::vector<std::shared_ptr<Network::Interface> > &clients, Network::PacketRegister &registerPacket, std::function<void(unsigned int)> onReceivePacket)
    : _outMessages(nullptr), _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _inMessages(inMessages),_tick(tick), _headerIn(), _headerOut(), _bodyOut(), _bodyIn(), _socketMutex(), _packetIn(), _packetOut(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _onConnect(std::move(onConnect)), _type(Type::SERVER), _clients(&clients), _forwardMessages(&forwardMessages), _currentSequenceNumber(0), _tempEndpoint(), _registerPacket(registerPacket), _onReceivePacket(std::move(onReceivePacket))
{
    _headerIn.bodySize = 0;
    _id = -1;
    _headerOut.bodySize = 0;
}

void Network::PacketIO::readPacket()
{
    _socketIn.async_receive_from(
        boost::asio::buffer(_tempBuffer), _tempEndpoint,
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::shared_ptr<Network::Packet> receivedPacket = std::make_shared<Network::Packet>();
                if (_type == Type::SERVER) {
                    _endpoint = _tempEndpoint;
                }
                memcpy(&receivedPacket->header, _tempBuffer.data(), sizeof(PacketHeader));
                if (receivedPacket->header.magicNumber != MAGIC_NUMBER) {
                    readPacket();
                    std::cout << "Error reading packet: magic number is not correct" << std::endl;
                    return;
                }
                if (_packetQueue.isQueueFull()) {
                    readPacket();
                    return;
                }
                if (_id == -1 || _type == Type::SERVER) {
                    _id = EndpointGetter::getIdByEndpoint(_endpoint, _clients);
                }
                receivedPacket->body.assign(_tempBuffer.begin() + sizeof(PacketHeader), _tempBuffer.begin() + length);
                if (_registerPacket.isPacketRegisteredIn(_id, receivedPacket->header.sequenceNumber)) {
                    readPacket();
                    return;
                }
                _onReceivePacket(_id);
                _registerPacket.registerReceivedPacket(_id, receivedPacket->header.sequenceNumber);
                _packetQueue.pushBack(std::make_pair(_endpoint, receivedPacket));
            } else {
                std::cout << "Error reading packet: " << ec.message() << std::endl;
            }
            readPacket();
        });
}


void Network::PacketIO::sendWaitingPackets()
{
    if (!_packetOutQueue.empty()) {
        _packetOut = _packetOutQueue.popFront()  ;
        writePacket();
    }
}

void Network::PacketIO::serializePacket()
{
    if (_packetOut == nullptr || _packetOut->body.empty() || _packetOut->header.bodySize == 0) {
        _serializedPacket.resize(0);
        return;
    }
    _serializedPacket.resize(sizeof(PacketHeader) + _packetOut->body.size());
    memcpy(_serializedPacket.data(), &_packetOut->header, sizeof(PacketHeader));
    memcpy(_serializedPacket.data() + sizeof(PacketHeader), _packetOut->body.data(), _packetOut->body.size());
}

void Network::PacketIO::writePacket()
{
    serializePacket();
    _socketOut.async_send_to(
        boost::asio::buffer(_serializedPacket.data(), _serializedPacket.size()), _endpoint,
        [this](std::error_code ec, std::size_t length) {
            if (!ec) {
                _tick.updateLastWriteTime();
                sendWaitingPackets();
            } else {
                std::cout << "Error writing packet" << ec.message() << std::endl;
            }
        });
}

void Network::PacketIO::processIncomingMessages() {
    boost::asio::post(_context, [this]() {
        /*
        _packetQueue.sortQueue(
            [](const std::pair<boost::asio::ip::udp::endpoint, std::shared_ptr<Network::Packet>>& a,
               const std::pair<boost::asio::ip::udp::endpoint, std::shared_ptr<Network::Packet>>& b) {
                return a.second->header.sequenceNumber < b.second->header.sequenceNumber;
            }
        );
        */
        while (!_packetQueue.empty()) {
            std::shared_ptr<Network::Packet> rawData = _packetQueue.getFront().second;
            boost::asio::ip::udp::endpoint endpoint = _packetQueue.getFront().first;
            _packetQueue.popFront();

            if (rawData == nullptr)  {
                continue;
            }
            _headerIn = rawData->header;
            _bodyIn.clear();
            _bodyIn.getData().assign(rawData->body.begin(), rawData->body.end());

            if (_type == Type::SERVER) {
                _onConnect(_endpoint);
            }
            if (_headerIn.bodySize == 0) {
                continue;
            }
            resendLostPacket(endpoint);
            size_t index = 0;
            unsigned int id = 0;
            std::uint16_t size = 0;
            while (index < _headerIn.bodySize) {
                if (_inMessages.isQueueFull()) {
                    break;
                }
                memcpy(&size, _bodyIn.getData().data() + index, sizeof(uint16_t));
                size = ntohs(size);
                if (size > _headerIn.bodySize || index > _headerIn.bodySize - sizeof(uint16_t) || index + size + sizeof(uint16_t) > _headerIn.bodySize) {
                    break;
                }
                try {
                    std::vector<std::uint8_t> subData(_bodyIn.getData().begin() + index, _bodyIn.getData().begin() + index + size + sizeof(uint16_t));
                    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::AMessage>(subData);
                    id = EndpointGetter::getIdByEndpoint(_endpoint, _clients);
                    std::shared_ptr<Network::OwnedMessage> ownedMessage = std::make_shared<Network::OwnedMessage>(id, message);
                    _inMessages.pushBack(ownedMessage);
                    index += size + sizeof(uint16_t);
                } catch (std::length_error &e) {
                    std::cout << "Error in processIncomingMessages : " << e.what() << std::endl;
                }
            }

        }
        while (!_inMessages.empty()) {
            std::shared_ptr<OwnedMessage> message = _inMessages.getFront();
            if (message == nullptr) {
                if (_inMessages.empty())
                    break;
                _inMessages.popFront();
                continue;
            }
            _forwardMessages->pushBack(message);
            if (_inMessages.empty())
                break;
            _inMessages.popFront();
        }
    });
}


void Network::PacketIO::processOutgoingMessages()
{
    boost::asio::post(_context, [this]() {
            uint16_t size = 0;
            bool isPacketSecure = false;
            if (!_outMessages || _outMessages->empty()) {
                return;
            }
            _bodyOut.clear();
            while (!_outMessages->empty()) {
                std::shared_ptr<IMessage> message= _outMessages->getFront();
                if (message == nullptr) {
                    if (_outMessages->empty())
                        break;
                    _outMessages->popFront();
                    continue;
                }
                if (size + message->getSize() > MAX_PACKET_SIZE)
                    break;
                _outMessages->popFront();
                _bodyOut.addData( message->getMessage() );
                size += message->getSize();
                if (message->isSecure())
                    isPacketSecure = true;
            }
            _packetOut = std::make_shared<Network::Packet>();
            if (_packetOut == nullptr)
                return;
            _packetOut->header.bodySize= size;
            _packetOut->header.sequenceNumber= _currentSequenceNumber++;
            if (_id == -1) {
                _id = EndpointGetter::getIdByEndpoint(_endpoint, _clients);
            }
            _packetOut->header.ackMask = 0;//_registerPacket.getAckMask(_id);
            _packetOut->header.lastPacketSeq = _registerPacket.getLastPacketId(_id);
            _registerPacket.registerSentPacket(_id, _packetOut, isPacketSecure);

            _packetOut->body= _bodyOut.getData();
            if (_packetOut->header.bodySize > 0) {
                _packetOutQueue.pushBack(_packetOut);
                sendWaitingPackets();
            }
    });
}

size_t Network::PacketIO::getOutMessagesSize() const
{
    return _outMessages->count();
}

void Network::PacketIO::resendLostPacket(boost::asio::ip::udp::endpoint &endpoint)
{
    return;
    uint16_t ackMask = 0;
    std::vector<std::shared_ptr<Network::Packet>> packets = {};

    unsigned int id = EndpointGetter::getIdByEndpoint(endpoint, _clients);

    if (id == -1) {
        return;
    }
    ackMask = _registerPacket.getAckMask(id);
    packets = _registerPacket.getPacketsToResend(id, ackMask);
    for (auto& packet : packets) {
        packet->header.sequenceNumber = _currentSequenceNumber++;
        _packetOutQueue.pushBack(packet);
    }
}

void Network::PacketIO::clearOutMessages()
{
    _outMessages->clear();
}
