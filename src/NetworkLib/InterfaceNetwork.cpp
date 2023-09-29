//
// Created by Clément Lagasse on 28/09/2023.
//

#include "InterfaceNetwork.hpp"

Network::Interface::Interface(asio::io_context &Context, TSQueue<OwnedMessage> &inMessages, std::optional<std::reference_wrapper<asio::ip::udp::socket>> inSocket,
                               Network::Tick &tick, const std::optional<std::function<void()>>& callbackFunction, Network::Interface::Type type) :
        _context(Context), _socket(Context), _endpoint(), _resolver(Context), _outMessages(), _type(type), _tick(tick),
        _packetIO(Context, _endpoint, inSocket.has_value() ? inSocket->get() : _socket, _socket, inMessages, _outMessages, _tick, callbackFunction) {
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
    getIO().readHeader();
}

void Network::Interface::send(const std::shared_ptr<IMessage>& message)
{
    if (isConnected()) {
        _outMessages.pushBack(message);
    }
}

asio::ip::udp::endpoint &Network::Interface::getEndpoint()
{
    return _endpoint;
}

Network::PacketIO &Network::Interface::getIO()
{
    return _packetIO;
}
