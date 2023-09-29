//
// Created by Clément Lagasse on 29/09/2023.
//

#include <iostream>
#include <utility>
#include "PacketIO.hpp"

Network::PacketIO::PacketIO( asio::io_context& context, asio::ip::udp::endpoint& endpoint, asio::ip::udp::socket& socketIn, asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages, Network::Tick& tick, const std::optional<std::function<void()>>& callbackListen)
: _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _outMessages(outMessages), _inMessages(inMessages),_tick(tick), _header(), _body(), _socketMutex(), _packet(), _callbackListen(callbackListen.has_value() ? callbackListen.value():  [this](){readHeader();})
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

void Network::PacketIO::readHeader()
{
    _socketIn.async_receive_from(
        asio::buffer(&_header, sizeof(_header)), _endpoint,
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "Header received : " << _header.bodySize
                          << std::endl;
                readBody();
            }
        });
}

void Network::PacketIO::readBody()
{
    _socketIn.async_receive_from(
        asio::buffer(_body.getData(), _header.bodySize), _endpoint,
        [&](std::error_code ec, std::size_t length) {
            std::cout << "Body received : " << _header.bodySize << std::endl;
            if (!ec) {
                size_t index = 0;
                while (index < _body.getSize()) {
                    std::shared_ptr<Network::Message> message =
                        std::make_shared<Network::Message>(_body.getData());
                    _inMessages.pushBack({this->shared_from_this(), message});
                    index += message->getSize();
                }
            } else {
                std::cout << "Error reading body" << ec.message() << std::endl;
            }
        });
}

void Network::PacketIO::writePacket()
{
    _socketOut.async_send_to(
        asio::buffer(&_packet, sizeof(_packet)), _endpoint,
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
            size_t size= 0;
            while ( !_outMessages.empty() ) {
                std::shared_ptr<IMessage> message= _outMessages.getFront();
                _outMessages.popFront();
                _body.addData( message->getMessage() );
                size+= message->getSize();
            }
            _packet.header.bodySize= size;
            _packet.header.sequenceNumber= 0;
            _packet.header.ackMask= 0;
            _packet.header.lastPacketSeq= 0;
            _packet.body = _body.getData();
            if (_packet.header.bodySize > 0)
                writePacket();
            _tick._processOutgoing= false;
        }
    });
}