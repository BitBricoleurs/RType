//
// Created by Clément Lagasse on 28/09/2023.
//

#include "InterfaceNetwork.hpp"

Network::Interface::Interface(asio::io_context &Context, TSQueue<OwnedMessage> &inMessages, std::optional<std::reference_wrapper<asio::ip::udp::socket>> inSocket,
                               Network::Tick &tick, unsigned int id, Network::Interface::Type type) :
        _context(Context), _socket(Context), _endpoint(), _resolver(Context), _outMessages(), _type(type), _tick(tick), _id(id)
{
    if (type == Type::SERVER) {
        if (_endpoint.address().is_v4())
            _socket.open(asio::ip::udp::v4());
        else
            _socket.open(asio::ip::udp::v6());
    }
    _packetIO = std::make_shared<Network::PacketIO>(_context, _endpoint, inSocket.has_value() ? inSocket->get() : _socket, _socket, inMessages, _outMessages, _tick);
    _id = 0;
}

Network::Interface::~Interface() {
    disconnect();
}

bool Network::Interface::isConnected() {
    return _socket.is_open();
}

void Network::Interface::disconnect()
{
    if (isConnected()) {
        _socket.close();
    }
}

void Network::Interface::connectToServer(const std::string &host, unsigned short port)
{
    _endpoint = *_resolver.resolve(host, std::to_string(port)).begin();
    if (_endpoint.address().is_v4())
        _socket.open(asio::ip::udp::v4());
    else
        _socket.open(asio::ip::udp::v6());
    getIO()->readPacket();
}

void Network::Interface::send(const std::shared_ptr<IMessage>& message)
{
    if (isConnected()) {
        _outMessages.pushBack(message);
    }
}

void Network::Interface::setEndpoint(const asio::ip::udp::endpoint &endpoint)
{
    _endpoint = endpoint;
}

asio::ip::udp::endpoint &Network::Interface::getEndpoint()
{
    return _endpoint;
}

std::shared_ptr<Network::PacketIO> Network::Interface::getIO()
{
    return _packetIO;
}

unsigned int Network::Interface::getId() const
{
    return _id;
}