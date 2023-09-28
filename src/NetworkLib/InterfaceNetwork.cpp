//
// Created by Clément Lagasse on 28/09/2023.
//

#include "InterfaceNetwork.hpp"

Network::Interface::Interface(asio::io_context &Context, TSQueue<OwnedMessage> &inMessages, Network::Tick &tick, Network::Interface::Type type) :
        _context(Context), _socket(Context), _endpoint(), _resolver(Context), _outMessages(), _tempHeader(),
        _inMessages(inMessages), _type(type), _tick(tick) {
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
    readHeader();
}

void Network::Interface::send(const std::shared_ptr<IMessage>& message)
{
    if (isConnected()) {
        _outMessages.pushBack(message);
    }
}

void Network::Interface::processOutgoingMessages()
{
    asio::post(_context, [this]() {
        std::unique_lock<std::mutex> lock(_tick._mtx);
        _tick._cvOutgoing.wait(lock, [this]() { return _tick._processOutgoing; });
        size_t size = 0;
        while (!_outMessages.empty()) {
            std::shared_ptr<IMessage> message = _outMessages.getFront();
            _outMessages.popFront();
            _tempBody.addData(message->getMessage());
            size += message->getSize();
            std::cout << "Message sent : " << message->getSize() << std::endl;
        }
        _tempHeader.bodySize = size;
        WriteHeader();
        _tick._processOutgoing = false;
        processOutgoingMessages();
    });
}

asio::ip::udp::endpoint &Network::Interface::getEndpoint()
{
    return _endpoint;
}

void Network::Interface::processReceivedHeader(const PacketHeader& header, const std::function<void()>& callbackAfterRead)
{
    _tempHeader = header;

    if (_tempHeader.bodySize > 0) {
        readBody([this, callbackAfterRead]() {
            callbackAfterRead();
        });
    }
}

void Network::Interface::readHeader()
{
    _socket.async_receive_from(
            asio::buffer(&_tempHeader, sizeof(Network::PacketHeader)), _endpoint,
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Header received : " << _tempHeader.bodySize << std::endl;
                    if (_tempHeader.bodySize > 0) {
                        readBody([this]() {
                            readHeader();
                        });
                    }
                } else {
                    std::cout << "Error reading header" << std::endl;
                    _socket.close();
                }
            });
}

void Network::Interface::readBody(const std::function<void()>& callbackAfterRead) {
    _socket.async_receive_from(
            asio::buffer(_tempBody.getData(), _tempHeader.bodySize), _endpoint,
            [this, callbackAfterRead](std::error_code ec, std::size_t length) {
                if (!ec) {
                    size_t index = 0;
                    while (index < _tempBody.getSize()) {
                        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>(_tempBody.getData());
                        if (_type == Network::Interface::Type::SERVER) {
                            _inMessages.pushBack({this->shared_from_this(), message});
                        } else {
                            _inMessages.pushBack({nullptr, message});
                        }
                        index += message->getSize();
                    }
                    if (callbackAfterRead) {
                        callbackAfterRead();
                    }

                } else {
                    std::cout << "Error reading body" << std::endl;
                    _socket.close();
                }
            });
}


void Network::Interface::WriteHeader()
{
    _socket.async_send_to(
            asio::buffer(&_tempHeader, sizeof(Network::PacketHeader)), _endpoint,
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    if (_tempHeader.bodySize > 0) {
                        WriteBody();
                    }
                } else {
                    std::cout << "Error writing header" << std::endl;
                    _socket.close();
                }
            });
}

void Network::Interface::WriteBody()
{
    _socket.async_send_to(
            asio::buffer(_tempBody.getData(), _tempHeader.bodySize), _endpoint,
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    _tick.lastWriteTimeMtx.lock();
                    _tick.lastPacketSent = std::chrono::high_resolution_clock::now();
                    _tick.lastWriteTimeMtx.unlock();
                } else {
                    std::cout << "Error writing body" << std::endl;
                    _socket.close();
                }
            });
}
