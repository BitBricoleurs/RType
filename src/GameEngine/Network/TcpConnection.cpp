//
// Created by Theophilus Homawoo on 25/10/2023.
//

#include "TcpConnection.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>
#include "Logger.hpp"
#include "GameEngine.hpp"

namespace GameEngine {
    TcpConnection::pointer TcpConnection::create(boost::asio::io_service& io_service) {
        return pointer(new TcpConnection(io_service));
    }

    boost::asio::ip::tcp::socket& TcpConnection::socket() {
        return socket_;
    }

    void TcpConnection::sendLog(const std::string& message) {
        boost::asio::async_write(socket_, boost::asio::buffer(message),
                                 boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

    TcpConnection::TcpConnection(boost::asio::io_service& io_service) : socket_(io_service) {
    }

    void TcpConnection::handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
        } else {
            Logger::wantsToReceiveLogs = false;
            std::cerr << "Failed to send message: " << error.message() << "\n";
        }
    }

    void TcpConnection::receiveMessage() {
        boost::asio::async_read_until(socket_, buffer_, '\n',
                                      boost::bind(&TcpConnection::handleRead, shared_from_this(),
                                                  boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred));
    }

    void TcpConnection::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            std::istream is(&buffer_);
            std::string message;
            std::getline(is, message);
            sendLog(GameEngine::handleDevConsole(message));

            receiveMessage();
        } else {
            Logger::wantsToReceiveLogs = false;
            Logger::error("Failed to receive message: " + error.message());
        }
    }
}
