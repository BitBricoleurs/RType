//
// Created by Theophilus Homawoo on 01/10/2023.
//

#include "SocketServer.hpp"

namespace GameEngine {

    SocketServer::SocketServer() :
    acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345))
    {
        startAccept();
    }


    SocketServer::~SocketServer() {
        stop();
    }

    void SocketServer::run() {
        io_service.run();
    }

    void SocketServer::stop() {
        io_service.stop();
        if (socket && socket->is_open()) {
            socket->close();
        }
    }

    void SocketServer::startAccept() {
        socket = std::make_shared<asio::ip::tcp::socket>(io_service);
        acceptor.async_accept(*socket, [this](const asio::error_code& error) {
            handleAccept(socket, error);
        });
    }

    void SocketServer::handleAccept(std::shared_ptr<asio::ip::tcp::socket> socket, const asio::error_code& error) {
        if (!error) {
            std::cout << "Client connected" << std::endl;
            awaitCommands(socket);
        }
    }

    void SocketServer::respond(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& message) {
        if (socket && socket->is_open()) {
            asio::write(*socket, asio::buffer(message));
        }
    }

    void SocketServer::awaitCommands(std::shared_ptr<asio::ip::tcp::socket> socket) {
        if (socket && socket->is_open()) {
            auto buffer = std::make_shared<asio::streambuf>();
            asio::async_read_until(*socket, *buffer, '\n',
                                   [this, socket, buffer](const asio::error_code& ec, std::size_t bytes_transferred) {
                                       if (!ec) {
                                           std::istream input(buffer.get());
                                           std::string command;
                                           std::string args;
                                           input >> command;
                                           std::getline(input, args);

                                           if (command == "exit") {
                                               std::cout << "Client disconnected" << std::endl;
                                               stop();
                                               return;
                                           } else {
                                           }
                                           awaitCommands(socket);
                                       } else {
                                           std::cerr << "Error while reading: " << ec.message() << std::endl;
                                       }
                                   });
        } else {
            std::cout << "Socket is not open" << std::endl;
        }
    }

}
