//
// Created by Theophilus Homawoo on 29/10/2023.
//

#include "LoggerImpl.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>

namespace GameEngine {
    boost::asio::io_service LoggerImpl::io_service;
    TcpConnection::pointer LoggerImpl::connection;

    LoggerImpl::LoggerImpl() {}

    LoggerImpl::~LoggerImpl() {
        io_service.stop();
        if (io_service_thread.joinable()) {
            io_service_thread.join();
        }
    }

    void LoggerImpl::startServer(unsigned short port) {
        try {
            std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
            TcpConnection::pointer new_connection = TcpConnection::create(io_service);

            acceptor->async_accept(new_connection->socket(),
                boost::bind(&LoggerImpl::handleAccept, this, new_connection,
                            acceptor,
                            boost::asio::placeholders::error));

            io_service_thread = std::thread([this](){ io_service.run(); });
        } catch (std::exception& e) {
            std::cerr << "Server Error: " << e.what() << std::endl;
        }
    }

    void LoggerImpl::sendLog(const std::string& message) {
        if (isConnectionAvailable()) {
            connection->sendLog(message);
        } else {
            std::cout << message;
        }
    }

    bool LoggerImpl::isConnectionAvailable() const {
        return connection != nullptr;
    }

    void LoggerImpl::handleAccept(TcpConnection::pointer new_connection, std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor, const boost::system::error_code& error) {
        if (!error) {
            connection = new_connection;
            new_connection->receiveMessage();

            TcpConnection::pointer new_connection = TcpConnection::create(io_service);
            acceptor->async_accept(new_connection->socket(),
                                  boost::bind(&LoggerImpl::handleAccept, this, new_connection,
                                              boost::ref(acceptor),
                                              boost::asio::placeholders::error));
        } else if (error) {
            if (error == boost::asio::error::operation_aborted) {
                std::cout << "Accept operation canceled, shutting down..." << std::endl;
                return;
            } else {
                std::cerr << "Accept Error: " << error.message() << std::endl;
            }
        }
    }
}