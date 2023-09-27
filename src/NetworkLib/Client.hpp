//
// Created by Clément Lagasse on 27/09/2023.
//

#pragma once

#include <any>
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <thread>
#include "Tick.hpp"
#include "Message.hpp"
#include "TSqueue.hpp"
#include "InterfaceNetwork.hpp"

namespace Network {
    class Client {
    public:
        Client(std::size_t tick)
        : _context(), _tick(tick)
        {
        }
        ~Client() = default;

        void connect(std::string &host, unsigned short port) {
            _interface = std::make_unique<Network::Interface>(_context, _inMessages, _tick, Network::Interface::Type::CLIENT);
            _interface->connectToServer(host, port);

            processIncomingMessages();
            _interface->processOutgoingMessages();

            _tickThread = std::thread([this]() {_tick.Start();});
            _listenThread = std::thread([this]() {_context.run(); });
            _receiveThread = std::thread([this]() {_context.run(); });
            _sendThread = std::thread([this]() {_context.run(); });
        }
        void disconnect() {
            if (isConnected()) {
                _interface->disconnect();
                if (_tickThread.joinable())
                    _tickThread.join();
                if (_receiveThread.joinable())
                    _receiveThread.join();
                if (_sendThread.joinable())
                    _sendThread.join();
                _interface.release();
            }
        }
        bool isConnected() const {
            return _interface->isConnected();
        }
        void send(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::vector<std::any> args) {
            if (!isConnected()) {
                return;
            }
            std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>(action, IDs, typeArg, args);
            _interface->send(message);
        }
    private:

        void processIncomingMessages() {
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

        Network::Tick _tick;
        std::unique_ptr<Network::Interface> _interface;
        asio::io_context _context;

        std::thread _listenThread;
        std::thread _tickThread;
        std::thread _receiveThread;
        std::thread _sendThread;

        Network::TSQueue<Network::OwnedMessage> _inMessages;
    };
}
