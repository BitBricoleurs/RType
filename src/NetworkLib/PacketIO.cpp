//
// Created by Clément Lagasse on 29/09/2023.
//

#include <iostream>
#include <utility>
#include "PacketIO.hpp"

Network::PacketIO::PacketIO( asio::io_context& context, asio::ip::udp::endpoint& endpoint, asio::ip::udp::socket& socketIn, asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages, Network::Tick& tick)
: _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _outMessages(&outMessages), _inMessages(inMessages),_tick(tick), _header(), _body(), _socketMutex(), _packet(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _type(Type::CLIENT)
{
    _header.bodySize = 0;

}

Network::PacketIO::PacketIO( asio::io_context& context, asio::ip::udp::endpoint& endpoint, asio::ip::udp::socket& socketIn, asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages, Network::Tick& tick, std::function<void(asio::ip::udp::endpoint &endpoint)> onConnect)
    : _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _inMessages(inMessages),_tick(tick), _header(), _body(), _socketMutex(), _packet(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _onConnect(std::move(onConnect)), _type(Type::SERVER), _outMessages(nullptr)
{
    _header.bodySize = 0;
}

void Network::PacketIO::setHeader(const Network::PacketHeader &header)
{
    _header = header;
}

void Network::PacketIO::setBody(const Network::Body &body)
{
    _body = body;
}

void Network::PacketIO::readPacket()
{
    _socketIn.async_receive_from(
        asio::buffer(_tempBuffer), _endpoint,
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                if (length >= sizeof(PacketHeader)) {
                    memcpy(&_header, _tempBuffer.data(), sizeof(PacketHeader));
                    std::cout << "Header received : " << _header.bodySize << std::endl;

                    if (length >= sizeof(PacketHeader) + _header.bodySize) {
                        _body.clear();
                        _body.getData().resize(_header.bodySize);
                        memcpy(_body.getData().data(), _tempBuffer.data() + sizeof(PacketHeader), _header.bodySize);
                        std::cout << "Body received : " << _header.bodySize << std::endl;

                        if (_type == Type::SERVER) {
                            _onConnect(_endpoint);
                        }
                        size_t index = 0;
                        while (index < _header.bodySize) {
                            std::shared_ptr<Network::Message> message =
                                std::make_shared<Network::Message>(_body.getData());
                            _inMessages.pushBack({this->shared_from_this(), message});
                            index += message->getSize();
                        }
                        readPacket();
                    } else {
                        std::cerr << "Error reading packet: body size is too small" << std::endl;
                    }
                } else {
                    std::cerr << "Error reading packet: header size is too small" << std::endl;
                }
            } else {
                std::cout << "Error reading packet: " << ec.message() << std::endl;
            }
        });
}

void Network::PacketIO::serializePacket()
{
    _serializedPacket.resize(sizeof(PacketHeader) + _packet.body.size());
    memcpy(_serializedPacket.data(), &_packet.header, sizeof(PacketHeader));
    memcpy(_serializedPacket.data() + sizeof(PacketHeader), _packet.body.data(), _packet.body.size());
}

void Network::PacketIO::writePacket()
{
    serializePacket();
    _socketOut.async_send_to(
        asio::buffer(_serializedPacket.data(), _serializedPacket.size()), _endpoint,
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                _tick.updateLastWriteTime();
                std::cout << "Packet sent : " << _packet.header.bodySize
                          << std::endl;
            } else {
                std::cout << "Error writing packet" << ec.message()
                          << std::endl;
            }
        });
}

void Network::PacketIO::processOutgoingMessages()
{
    asio::post(_context, [this]() {
        while (1) {
            std::unique_lock<std::mutex> lock( _tick._mtx );
            _tick._cvOutgoing.wait( lock, [ this ]() {
                return _tick._processOutgoing;
            } );
            uint16_t size= 0;
            if (!_outMessages || _outMessages->empty()) {
                _tick._processOutgoing= false;
                continue;
            }
            while (!_outMessages->empty()) {
                std::shared_ptr<IMessage> message= _outMessages->getFront();
                _outMessages->popFront();
                _body.addData( message->getMessage() );
                size+= message->getSize();
            }
            _packet.header.bodySize= size;
            _packet.header.sequenceNumber= 0;
            _packet.header.ackMask= 0;
            _packet.header.lastPacketSeq= 0;
            _packet.body= _body.getData();
            if (_packet.header.bodySize > 0)
                writePacket();
            _tick._processOutgoing= false;
        }
    });
}