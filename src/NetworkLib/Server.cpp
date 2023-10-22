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
      Impl(unsigned short port, size_t maxClients, size_t Tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue)
          : _context(), _idleWork(std::make_unique<boost::asio::io_context::work>(_context)), _tick(Tick), _socket(_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _running(true), _port(port), _maxClients(maxClients), _inMessages(),
            _tempPacket(), _tempBuffer(MAX_PACKET_SIZE + sizeof(Network::PacketHeader)), _indexId(0), _forwardQueue(forwardQueue)
      {

          _packetIO = std::make_shared<Network::PacketIO>(_context, _remoteEndpoint, _socket, _socket, _inMessages, _forwardQueue, _tick,
                                                          [this](boost::asio::ip::udp::endpoint &endpoint) {
                                                                registerNewCon(endpoint);
                                                          }, _clients);
            int maxThreads = std::thread::hardware_concurrency();
            int ideaThread = 2 + 2 * maxClients;
            if (ideaThread > maxThreads) {
                ideaThread = maxThreads;
            }
            for (size_t i = 0; i < ideaThread; i++) {
                _pool.push_back(std::thread([&]() { _context.run(); }));
            }
            boost::asio::ip::udp::endpoint local_ep = _socket.local_endpoint();
            std::string listening_ip = local_ep.address().to_string();
            unsigned short listening_port = local_ep.port();

            std::cout << "Listening on IP: " << listening_ip << ", Port: " << listening_port << std::endl;

        }

        ~Impl() {
            stop();
        }

        void start() {
            _tickThread = std::thread([this]() {_tick.Start();});
            _tick.setIncomingFunction([this]() {_packetIO->processIncomingMessages();});
            _tick.setOutgoingFunction([this]() {
            for (auto &client : _clients) {
                if (client && client->isConnected()) {
                    client->getIO()->processOutgoingMessages();
                }
            }
            });
            _packetIO->readPacket();
            _packetIO->processIncomingMessages();
        }

        void stop() {
            _idleWork.reset();
            _context.stop();
            _tick.Stop();
            if (_tickThread.joinable())
                _tickThread.join();
            for (auto &thread: _pool) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
        }

        bool isConnectionOpen(const boost::asio::ip::udp::endpoint& endpoint) {
            for (const auto& client : _clients) {
                if (client->getEndpoint() == endpoint) {
                    return true;
                }
            }
            return false;
        }


        void sendClient(unsigned int id, const std::shared_ptr<IMessage>& message)
        {
            for (auto &client : _clients) {
                if (client && client->isConnected() && client->getId() == id) {
                    client->send(message);
                }
            }
        }

        void sendClients(const std::vector<unsigned int> &ids, const std::shared_ptr<IMessage>& message)
        {
            for (auto id : ids) {
                for (auto &client : _clients) {
                    if (client && client->isConnected() && client->getId() == id) {
                        client->send(message);
                    }
                }
            }
        }

        void sendAllClients(const std::shared_ptr<IMessage>& message)
        {
            for (auto &client : _clients) {
                if (client && client->isConnected()) {
                    client->send(message);
                }
            }
        }

        void sendAllClientsExcept(unsigned int id, const std::shared_ptr<IMessage>& message)
        {
            for (auto &client : _clients) {
                if (client && client->isConnected() && client->getId() != id) {
                    client->send(message);
                }
            }
        }

         Network::TSQueue<unsigned int> &getConnectedClients()
        {
            return _connectingClients;
        }

        Network::TSQueue<unsigned int>& getDisconnectedClients()
        {
            return _disconnetingClients;
        }

        void disconnectClient(unsigned int id) {
          int i = 0;
           for (auto &client : _clients) {
               if (client && client->isConnected() && client->getId() == id) {
                   client->disconnect();
                   _disconnetingClients.pushBack(id);
                   client.reset();
                   _clients.erase(_clients.begin() + i);
               }
                i++;
           }
        }

    private:
        std::shared_ptr<Interface> getInterfaceByEndpoint(const boost::asio::ip::udp::endpoint& endpoint) {
            for (const auto& client : _clients) {
                if (client->getEndpoint() == endpoint) {
                    return client;
                }
            }
            return nullptr;
        }

        void registerNewCon(boost::asio::ip::udp::endpoint &remoteEndpoint)
        {
            auto clientInterface
                = getInterfaceByEndpoint( remoteEndpoint );
            if (_clients.size() == _maxClients) {
                return;
            }
            if ( !clientInterface) {
                clientInterface = std::make_shared<
                    Network::Interface>(
                    _context, _inMessages, _socket, _forwardQueue, _tick, _indexId, Network::Interface::Type::SERVER
                );
                clientInterface->setEndpoint(remoteEndpoint);
                _clients.push_back( clientInterface );
                std::cout
                    << "New client connected : "
                    << remoteEndpoint.address().to_string()
                    << ":" << remoteEndpoint.port()
                    << " id is :" << _indexId << std::endl;
                clientInterface->getIO()->processOutgoingMessages();
                _connectingClients.pushBack(_indexId);
                _indexId++;
            }
        }


        Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &_forwardQueue;
        Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> _inMessages;
        boost::asio::io_context _context;
        std::unique_ptr<boost::asio::io_context::work> _idleWork;
        Network::Tick _tick;

        std::thread _tickThread;

        std::shared_ptr<Network::PacketIO> _packetIO;
        Network::Packet _tempPacket;
        std::vector<unsigned char> _tempBuffer;

        boost::asio::ip::udp::socket _socket;
        std::mutex _socketMutex;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        std::vector<std::thread> _pool;
        std::vector<std::shared_ptr<Network::Interface> > _clients;
        bool _running;
        unsigned short _port;
        size_t _maxClients;
        size_t _indexId;
        std::mutex _queueMutex;
        Network::TSQueue<unsigned int> _disconnetingClients;
        Network::TSQueue<unsigned int> _connectingClients;
    };

    Server::Server() : _isRunning(false), pimpl(nullptr) {}

    void Server::init(unsigned short port, size_t maxClients, size_t Tick, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &forwardQueue) {
        Server::getInstance().pimpl = std::make_unique<Impl>(port, maxClients, Tick, forwardQueue);
    }

    Server& Server::getInstance() {
        static Server instance;
        return instance;
    }

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

    void Server::sendClient(unsigned int id, const std::shared_ptr<IMessage>& message)
    {
        pimpl->sendClient(id, message);
    }

    void Server::sendClients(const std::vector<unsigned int> &ids, const std::shared_ptr<IMessage>& message)
    {
        pimpl->sendClients(ids, message);
    }

    void Server::sendAllClients(const std::shared_ptr<IMessage>& message)
    {
        pimpl->sendAllClients(message);
    }

    void Server::sendAllClientsExcept(unsigned int id, const std::shared_ptr<IMessage>& message)
    {
        pimpl->sendAllClientsExcept(id, message);
    }

    Network::TSQueue<unsigned int> &Server::getConnectedClients()
    {
        return pimpl->getConnectedClients();
    }

    Network::TSQueue<unsigned int> &Server::getDisconnectedClients()
    {
        return pimpl->getDisconnectedClients();
    }

    void Server::disconnectClient(unsigned int id) {
        pimpl->disconnectClient(id);
    }

}