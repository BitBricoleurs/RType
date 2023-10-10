//
// Created by Clément Lagasse on 28/09/2023.
//

#include <iostream>
#include <boost/asio.hpp>
#include <utility>
#include <optional>
#include "Client.hpp"
#include "Tick.hpp"
#include "TSqueue.hpp"
#include "InterfaceNetwork.hpp"

class Network::Client::Impl {
public:
    Impl(std::size_t tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue) :
            _tick(tick), _forwardQueue(forwardQueue) {}

    void connect(const std::string &host, unsigned short port);
    void disconnect();
    bool isConnected() const;
    void send(const std::shared_ptr<IMessage>& message);
    void waitForOutMessagesAndDisconnect();

    boost::asio::io_context _context;
    Network::Tick _tick;
    std::unique_ptr<Network::Interface> _interface;
    std::thread _tickThread;
    std::thread _listenThread;
    std::thread _receiveThread;
    std::thread _sendThread;

    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &_forwardQueue;
    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> _inMessages;
};

void Network::Client::Impl::connect(const std::string &host, unsigned short port) {
    _interface = std::make_unique<Network::Interface>(_context, _inMessages, std::nullopt, _forwardQueue, _tick, 0 , Network::Interface::Type::CLIENT);
    _interface->connectToServer(host, port);

    _interface->getIO()->processIncomingMessages();
    _interface->getIO()->processOutgoingMessages();
    _tick.setIncomingFunction([this]() {_interface->getIO()->processIncomingMessages();});
    _tick.setOutgoingFunction([this]() {_interface->getIO()->processOutgoingMessages();});

    _tickThread = std::thread([this]() {_tick.Start();});
    _listenThread = std::thread([this]() {_context.run(); });
    _receiveThread = std::thread([this]() {_context.run(); });
    _sendThread = std::thread([this]() {_context.run(); });
}

void Network::Client::Impl::waitForOutMessagesAndDisconnect() {
    while (_interface->getIO()->getOutMessagesSize() > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    _interface->disconnect();
}
void Network::Client::Impl::disconnect() {
    boost::asio::post(_context, [this]() {
        waitForOutMessagesAndDisconnect();
    });

    if (_tickThread.joinable())
        _tickThread.join();
    if (_receiveThread.joinable())
        _receiveThread.join();
    if (_sendThread.joinable())
        _sendThread.join();
    if (_listenThread.joinable())
        _listenThread.join();
    _interface.reset();
}

bool Network::Client::Impl::isConnected() const {
    if (!_interface)
        return false;
    return _interface->isConnected();
}

void Network::Client::Impl::send(const std::shared_ptr<IMessage>& message) {
    if (!isConnected()) {
        return;
    }
    _interface->send(message);
}


Network::Client::Client() : pimpl(nullptr) {}

void Network::Client::init(std::size_t tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue) {
    Network::Client::getInstance().pimpl = std::make_unique<Impl>(tick, forwardQueue);
}

Network::Client& Network::Client::getInstance() {
    static Network::Client instance;
    return instance;
}

void Network::Client::connect(const std::string &host, unsigned short port) {
    pimpl->connect(host, port);
}

void Network::Client::disconnect() {
    pimpl->disconnect();
}

bool Network::Client::isConnected() const {
    return pimpl->isConnected();
}

void Network::Client::send(const std::shared_ptr<IMessage>& message) {
    pimpl->send(message);
}

Network::Client::~Client() {
    std::cout << "Client destroyed" << std::endl;
}
