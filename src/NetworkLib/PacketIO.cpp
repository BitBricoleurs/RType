//
// Created by Clément Lagasse on 29/09/2023.
//

#include <iostream>
#include <utility>
#include "PacketIO.hpp"

Network::PacketIO::PacketIO(boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn, boost::asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages, TSQueue<std::shared_ptr<IMessage>>& outMessages, Network::Tick& tick)
: _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _outMessages(&outMessages), _inMessages(inMessages),_tick(tick), _headerIn(), _headerOut(), _bodyOut(), _bodyIn(), _socketMutex(), _packetIn(), _packetOut(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _type(Type::CLIENT), _clients(nullptr)
{
    _headerIn.bodySize = 0;
    _headerOut.bodySize = 0;
}

Network::PacketIO::PacketIO(boost::asio::io_context& context, boost::asio::ip::udp::endpoint& endpoint, boost::asio::ip::udp::socket& socketIn, boost::asio::ip::udp::socket& socketOut, TSQueue<Network::OwnedMessage>& inMessages, Network::Tick& tick, std::function<void(boost::asio::ip::udp::endpoint &endpoint)> onConnect, std::vector<std::shared_ptr<Network::Interface> > &clients)
    : _context(context), _endpoint(endpoint), _socketIn(socketIn), _socketOut(socketOut), _inMessages(inMessages),_tick(tick), _headerIn(), _headerOut(), _bodyOut(), _bodyIn(), _socketMutex(), _packetIn(), _packetOut(), _tempBuffer(MAX_PACKET_SIZE + sizeof(PacketHeader)), _onConnect(std::move(onConnect)), _type(Type::SERVER), _outMessages(nullptr), _clients(&clients)
{
    _headerIn.bodySize = 0;
    _headerOut.bodySize = 0;
}

void Network::PacketIO::readPacket()
{

    _socketIn.async_receive_from(
        boost::asio::buffer(_tempBuffer), _endpoint,
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                if (length >= sizeof(PacketHeader)) {
                    memcpy(&_headerIn, _tempBuffer.data(), sizeof(PacketHeader));
                    std::cout << "Header received : " << _headerIn.bodySize << std::endl;

                    if (length >= sizeof(PacketHeader) + _headerIn.bodySize) {
                        _bodyIn.clear();
                        _bodyIn.getData().resize(_headerIn.bodySize);
                        memcpy(_bodyIn.getData().data(), _tempBuffer.data() + sizeof(PacketHeader), _headerIn.bodySize);
                        std::cout << "Body received : " << _headerIn.bodySize << std::endl;

                        if (_type == Type::SERVER) {
                            _onConnect(_endpoint);
                        }
                        size_t index = 0;
                        while (index < _headerIn.bodySize) {
                            std::vector<std::uint8_t> subData(_bodyIn.getData().begin() + index, _bodyIn.getData().end());
                            std::shared_ptr<Network::Message> message =
                                std::make_shared<Network::Message>(subData);
                            _inMessages.pushBack({EndpointGetter::getIdByEndpoint(_endpoint, _clients), message});
                            index += message->getSize();
                        }
                    } else {
                        std::cerr << "Error reading packet: body size is too small" << std::endl;
                    }
                } else {
                    std::cerr << "Error reading packet: header size is too small" << std::endl;
                }
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
                std::cout << "Packet sent : " << _packetOut.header.bodySize
                          << std::endl;
            } else {
                std::cout << "Error writing packet" << ec.message()
                          << std::endl;
            }
        });
}

void Network::PacketIO::processOutgoingMessages()
{
    boost::asio::post(_context, [this]() {
        while (1) {
            std::unique_lock<std::mutex> lock( _tick._mtx );
            _tick._cvOutgoing.wait( lock, [ this ]() {
                return _tick._processOutgoing;
            } );
            uint16_t size = 0;
            if (!_outMessages || _outMessages->empty()) {
                _tick._processOutgoing= false;
                continue;
            }
            _bodyOut.clear();
            std::cout << "Nbr message" << _outMessages->count() << std::endl;
            while (!_outMessages->empty()) {
                std::shared_ptr<IMessage> message= _outMessages->getFront();
                _outMessages->popFront();
                _bodyOut.addData( message->getMessage() );
                size+= message->getSize();
            }
            _packetOut.header.bodySize= size;
            _packetOut.header.sequenceNumber= 0;
            _packetOut.header.ackMask= 0;
            _packetOut.header.lastPacketSeq= 0;
            _packetOut.body= _bodyOut.getData();
            if (_packetOut.header.bodySize > 0)
                writePacket();
            _tick._processOutgoing= false;
        }
    });
}
