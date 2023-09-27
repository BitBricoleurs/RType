//
// Created by Clément Lagasse on 27/09/2023.
//

#pragma once

#include <cstddef>
#include <iostream>
#include "Tick.hpp"
#include "PacketComponent.hpp"
#include "InterfaceNetwork.hpp"

namespace Network {
    class Server {
    public:
        Server(unsigned short port, size_t maxClients, size_t Tick)
        : _context(), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _port(port), _maxClients(maxClients), _running(false), _tick(Tick)
        {
            for (size_t i = 0; i < maxClients; i++) {
                _pool.push_back(std::thread([&]() { _context.run(); }));
            }
        };
        ~Server() = default;

        void start() {
            _tickThread = std::thread([this]() {_tick.Start();});

            ListenForNewCon();
        }

        void stop() {
            _context.stop();
            for (auto& thread : _pool) {
                if (thread.joinable()) {
                    thread.join();
                }
            }

        }

    private:

        std::shared_ptr<Interface> getInterfaceByEndpoint(const asio::ip::udp::endpoint& endpoint) {
            for (const auto& client : _clients) {
                if (client->getEndpoint() == endpoint) {
                    return client;
                }
            }
            return nullptr;
        }

        void ListenForNewCon() {
            _socket.async_receive_from(
                    asio::buffer(&_tempHeader, sizeof(Network::PacketHeader)), _remoteEndpoint,
                    [this](std::error_code ec, std::size_t bytesReceived) {
                        if (!ec) {
                            auto clientInterface = getInterfaceByEndpoint(_remoteEndpoint);
                            if (!clientInterface) {
                                clientInterface = std::make_shared<Network::Interface>(_context, _inMessages, _tick);
                                _clients.push_back(clientInterface);
                            }

                            clientInterface->processReceivedHeader(_tempHeader);
                            ListenForNewCon();
                        } else {
                        }
                    }
            );
        }

        bool isConnectionOpen(const asio::ip::udp::endpoint& endpoint) {
            for (const auto& client : _clients) {
                if (client->getEndpoint() == endpoint) {
                    return true;
                }
            }
            return false;
        }

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

        asio::io_context _context;
        Network::Tick _tick;

        std::thread _tickThread;

        Network::PacketHeader _tempHeader;
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _remoteEndpoint;
        std::vector<std::thread> _pool;
        std::vector<std::shared_ptr<Network::Interface>> _clients;
        bool _running;
        unsigned short _port;
        size_t _maxClients;
        Network::TSQueue<Network::OwnedMessage> _inMessages;
    };
}
