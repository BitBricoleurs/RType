//
// Created by Clément Lagasse on 28/09/2023.
//

#include <iostream>
#include <asio.hpp>
#include "Client.hpp"
#include "Tick.hpp"
#include "Message.hpp"
#include "TSqueue.hpp"
#include "InterfaceNetwork.hpp"

class Network::Client::Impl {
public:
    Impl(std::size_t tick) : _tick(tick) {}

    void connect(const std::string &host, unsigned short port);
    void disconnect();
    bool isConnected() const;
    void send(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::vector<std::any> args);
    void processIncomingMessages();

    asio::io_context _context;
    Network::Tick _tick;
    std::unique_ptr<Network::Interface> _interface;
    std::thread _tickThread;
    std::thread _listenThread;
    std::thread _receiveThread;
    std::thread _sendThread;
    Network::TSQueue<Network::OwnedMessage> _inMessages;
};

void Network::Client::Impl::connect(const std::string &host, unsigned short port) {
    _interface = std::make_unique<Network::Interface>(_context, _inMessages, _tick, Network::Interface::Type::CLIENT);
    _interface->connectToServer(host, port);

    processIncomingMessages();
    _interface->processOutgoingMessages();

    _tickThread = std::thread([this]() {_tick.Start();});
    _listenThread = std::thread([this]() {_context.run(); });
    _receiveThread = std::thread([this]() {_context.run(); });
    _sendThread = std::thread([this]() {_context.run(); });
}

void Network::Client::Impl::disconnect() {
    if (isConnected()) {
        _interface->disconnect();
        if (_tickThread.joinable())
            _tickThread.join();
        if (_receiveThread.joinable())
            _receiveThread.join();
        if (_sendThread.joinable())
            _sendThread.join();
        _interface.reset();
    }
}

bool Network::Client::Impl::isConnected() const {
    return _interface->isConnected();
}

void Network::Client::Impl::send(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::vector<std::any> args) {
    if (!isConnected()) {
        return;
    }
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>(action, IDs, typeArg, args);
    _interface->send(message);
}

void Network::Client::Impl::processIncomingMessages() {
    asio::post(_context, [this]() {
        std::unique_lock<std::mutex> lock(_tick._mtx);
        _tick._cvIncoming.wait(lock, [this]() { return _tick._processIncoming; });
        while (!_inMessages.empty()) {
            std::shared_ptr<IMessage> message = _inMessages.getFront().message;
            std::cout << "Message received : " << message->getSize() << std::endl;
            _inMessages.popFront();
        }
        _tick._processIncoming = false;
        processIncomingMessages();
    });
}

Network::Client::Client(std::size_t tick) : pimpl(std::make_unique<Impl>(tick)) {}

void Network::Client::connect(const std::string &host, unsigned short port) {
    pimpl->connect(host, port);
}

void Network::Client::disconnect() {
    pimpl->disconnect();
}

bool Network::Client::isConnected() const {
    return pimpl->isConnected();
}

void Network::Client::send(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::vector<std::any> args) {
    pimpl->send(action, IDs, typeArg, args);
}

Network::Client::~Client() = default;