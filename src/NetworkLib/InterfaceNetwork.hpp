//
// Created by Clément Lagasse on 20/09/2023.
//

#pragma once

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "Tick.hpp"
#include "IMessage.hpp"
#include "TSqueue.hpp"
#include "PacketComponent.hpp"
#include "Body.hpp"
#include "Message.hpp"

namespace Network {
    class Interface : public  std::enable_shared_from_this<Interface> {
    public:
        enum class Type {
            SERVER,
            CLIENT
        };

        Interface(asio::io_context &Context, TSQueue<OwnedMessage> &inMessages, Network::Tick &tick,
                  Network::Interface::Type type = Network::Interface::Type::CLIENT) :
                _context(Context), _socket(Context), _endpoint(), _resolver(Context), _outMessages(),
                _inMessages(inMessages), _type(type), _tick(tick) {
            _id = 0;
        };

        ~Interface() {
            disconnect();
        }

        bool isConnected() {
            return _socket.is_open();
        }

        void disconnect() {
            if (isConnected()) {
                _socket.close();
            }
        }


        void acceptClient(unsigned int id, const asio::ip::udp::endpoint &endpoint) {
            _endpoint = endpoint;
            if (isConnected()) {
                _id = id;
                readHeader();
            }
        }

        void connectToServer(const std::string &host, unsigned short port) {
            _endpoint = *_resolver.resolve(host, std::to_string(port)).begin();
            readHeader();
        }

        void send(std::shared_ptr<IMessage> message) {
                if (isConnected()) {
                    _outMessages.pushBack(message);
                }
        }

        void processOutgoingMessages() {
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

        asio::ip::udp::endpoint &getEndpoint() {
            return _endpoint;
        }

        void processReceivedHeader(const PacketHeader& header) {
            _tempHeader = header;

            if (_tempHeader.bodySize > 0) {
                readBody();
            }
        }
    private:

        void readHeader() {
            _socket.async_receive_from(
                    asio::buffer(&_tempHeader, sizeof(Network::PacketHeader)), _endpoint,
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            if (_tempHeader.bodySize > 0) {
                                readBody();
                            } else {
                                readHeader();
                            }
                        } else {
                            std::cout << "Error reading header" << std::endl;
                            _socket.close();
                        }
                    });
        }

            void readBody() {

            asio::async_read(_socket, asio::buffer(_tempBody.getData(), _tempHeader.bodySize),
                             [this](std::error_code ec, std::size_t length) {
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
                                    if (this->_type == Network::Interface::Type::CLIENT) {
                                        readHeader();
                                    }
                                 } else {
                                     std::cout << "Error reading body" << std::endl;
                                     _socket.close();
                                 }
                             });

        }

        void WriteHeader() {
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
        void WriteBody() {
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
            asio::io_context &_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _endpoint;
            asio::ip::udp::resolver _resolver;


            TSQueue<std::shared_ptr<IMessage>> _outMessages;
            TSQueue<OwnedMessage> &_inMessages;

            Network::PacketHeader _tempHeader;
            Network::Body _tempBody;

            unsigned int _id;

            Network::Interface::Type _type;

            Network::Tick &_tick;


    };
};
