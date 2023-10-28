//
// Created by Theophilus Homawoo on 25/10/2023.
//

#include "TcpConnection.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>

namespace GameEngine {
    TcpConnection::pointer TcpConnection::create(boost::asio::io_service& io_service) {
        return pointer(new TcpConnection(io_service));
    }

    boost::asio::ip::tcp::socket& TcpConnection::socket() {
        return socket_;
    }

    void TcpConnection::sendLog(const std::string& message) {
        boost::asio::async_write(socket_, boost::asio::buffer(message),
                                 boost::bind(&GameEngine::TcpConnection::handleWrite, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

    TcpConnection::TcpConnection(boost::asio::io_service& io_service) : socket_(io_service) {}

    void TcpConnection::handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            std::cout << "Successfully sent " << bytes_transferred << " bytes.\n";
        } else {
            std::cerr << "Failed to send message: " << error.message() << "\n";
        }
    }
}
