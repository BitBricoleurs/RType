//
// Created by Theophilus Homawoo on 29/10/2023.
//

#pragma once

#include <string>
#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include "TcpConnection.hpp"

#pragma once

#include "TcpConnection.hpp"
#include <boost/asio.hpp>
#include <memory>

namespace GameEngine {
    class LoggerImpl {
    public:
        LoggerImpl();
        ~LoggerImpl();

        void startServer(unsigned short port);
        void sendLog(const std::string& message);
        bool isConnectionAvailable() const;

    private:
        static TcpConnection::pointer connection;
        static boost::asio::io_service io_service;
        std::thread io_service_thread;

        void handleAccept(TcpConnection::pointer new_connection, std::shared_ptr<boost::asio::ip::tcp::acceptor>, const boost::system::error_code& error);
    };
}

