//
// Created by Clément Lagasse on 28/09/2023.
//

#include <iostream>
#include <thread>
#include "Tick.hpp"
#include "InterfaceNetwork.hpp"
#include "Server.hpp"

namespace Network {

    class Server::Impl {
    public:
      Impl(unsigned short port, size_t maxClients, size_t Tick)
          : _context(), _idleWork(std::make_unique<asio::io_context::work>(_context)), _tick(Tick), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _running(true), _port(port), _maxClients(maxClients), _inMessages(),
            _tempPacket(), _tempBuffer(MAX_PACKET_SIZE + sizeof(Network::PacketHeader))
      {
          _packetIO = std::make_shared<Network::PacketIO>(_context, _remoteEndpoint, _socket, _socket, _inMessages, _tick,
                                                          [this](asio::ip::udp::endpoint &endpoint) {
                                                                registerNewCon(endpoint);
                                                          });
            std::cout << _inMessages.empty() << std::endl;
            int maxThreads = std::thread::hardware_concurrency();
            int ideaThread = 2 + 2 * maxClients;
            if (ideaThread > maxThreads) {
                ideaThread = maxThreads;
            }
            std::cout << "Allocated Threads: " << ideaThread << std::endl;
            std::cout << "Max Threads: " << maxThreads << std::endl;
            for (size_t i = 0; i < ideaThread; i++) {
                _pool.push_back(std::thread([&]() { _context.run(); }));
            }
            asio::ip::udp::endpoint local_ep = _socket.local_endpoint();
            std::string listening_ip = local_ep.address().to_string();
            unsigned short listening_port = local_ep.port();

            std::cout << "Listening on IP: " << listening_ip << ", Port: " << listening_port << std::endl;

        }

        ~Impl() {
            stop();
        }

        void start() {
            _tickThread = std::thread([this]() {_tick.Start();});
            _packetIO->readPacket();
            processIncomingMessages();
            for (auto &client_interface : _clients) {
                client_interface->getIO()->processOutgoingMessages();
            }
            while (true) {
                if (_context.stopped()) {
                    std::cout << "io_context is stopped!" << std::endl;
                }
            }
        }

        void stop() {
            _idleWork.reset();
            _context.stop();
            if (_tickThread.joinable())
                _tickThread.join();
            for (auto &thread: _pool) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
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
                while (1) {
                    std::unique_lock<std::mutex> lock( _tick._mtx );
                    _tick._cvIncoming.wait( lock, [ this ]() {
                        return _tick._processIncoming;
                    } );
                    lock.unlock();
                    while ( !_inMessages.empty() ) {
                        Network::OwnedMessage message
                            = _inMessages.popFront();
                        std::cout << "Message received : " << message.message->getSize()
                                  << std::endl;
                        break;
                    }
                    _tick._processIncoming= false;
                }
            });
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

        void registerNewCon(asio::ip::udp::endpoint &remoteEndpoint)
        {
            auto clientInterface
                = getInterfaceByEndpoint( remoteEndpoint );
            if ( !clientInterface ) {
                clientInterface = std::make_shared<
                    Network::Interface>(
                    _context, _inMessages, _socket, _tick, Network::Interface::Type::SERVER
                );
                clientInterface->setEndpoint(remoteEndpoint);
                _clients.push_back( clientInterface );
                std::cout
                    << "New client connected : "
                    << remoteEndpoint.address().to_string()
                    << ":" << remoteEndpoint.port()
                    << std::endl;
            }
        }

        Network::TSQueue<Network::OwnedMessage> _inMessages;
        asio::io_context _context;
        std::unique_ptr<asio::io_context::work> _idleWork;
        Network::Tick _tick;

        std::thread _tickThread;

        std::shared_ptr<Network::PacketIO> _packetIO;
        Network::Packet _tempPacket;
        std::vector<unsigned char> _tempBuffer;

        asio::ip::udp::socket _socket;
        std::mutex _socketMutex;
        asio::ip::udp::endpoint _remoteEndpoint;
        std::vector<std::thread> _pool;
        std::vector<std::shared_ptr<Network::Interface> > _clients;
        bool _running;
        unsigned short _port;
        size_t _maxClients;
    };

    Server::Server(unsigned short port, size_t maxClients, size_t Tick)
            : pimpl(std::make_unique<Impl>(port, maxClients, Tick)) {}

    Server::~Server()
    {
        std::cout << "Server stopped" << std::endl;
    }

    void Server::start() {
        pimpl->start();
        _isRunning = true;
    }

    void Server::stop() {
        pimpl->stop();
        _isRunning = false;
    }

}
