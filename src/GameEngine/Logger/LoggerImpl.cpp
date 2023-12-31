//
// Created by Theophilus Homawoo on 29/10/2023.
//

#include "Logger.hpp"
#include "TcpConnection.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace GameEngine {
    std::unique_ptr<Logger::LoggerImpl> Logger::pimpl = std::make_unique<Logger::LoggerImpl>();

    struct Logger::LoggerImpl {
        static TcpConnection::pointer connection;
        static boost::asio::io_service io_service;
        static void handleAccept(TcpConnection::pointer new_connection, boost::asio::ip::tcp::acceptor& acceptor, const boost::system::error_code& error);
    };

    TcpConnection::pointer Logger::LoggerImpl::connection;
    boost::asio::io_service Logger::LoggerImpl::io_service;

    void Logger::log(int level, const std::string& message) {
        if (level < currentLogLevel) {
            return;
        }
        std::string log_level_str = levelToString(level);
        std::string timestamp = getCurrentTimestamp();
        std::string full_message = "[" + timestamp + "] [" + log_level_str + "] " + message + "\n";
        if (LoggerImpl::connection && wantsToReceiveLogs) {
            LoggerImpl::connection->sendLog(full_message);
        } else {
            std::cout << full_message;
        }
    }

    void Logger::startServer(unsigned short port) {
        try {
            boost::asio::ip::tcp::acceptor acceptor(LoggerImpl::io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
            TcpConnection::pointer new_connection = TcpConnection::create(LoggerImpl::io_service);

            std::string INFO = "Console Endpoint available at: " + acceptor.local_endpoint().address().to_string() + ":" + std::to_string(acceptor.local_endpoint().port());
            info(INFO);
            acceptor.async_accept(new_connection->socket(),
                                  boost::bind(&LoggerImpl::handleAccept, new_connection,
                                              boost::ref(acceptor),
                                              boost::asio::placeholders::error));

            LoggerImpl::io_service.run();
        } catch (std::exception& e) {
            std::cerr << "Server Error: " << e.what() << std::endl;
        }
    }

    void Logger::stopServer() {
        if (LoggerImpl::connection) {
            LoggerImpl::connection->stop();
        }
        LoggerImpl::io_service.stop();
    }

    void Logger::LoggerImpl::handleAccept(TcpConnection::pointer new_connection, boost::asio::ip::tcp::acceptor& acceptor, const boost::system::error_code& error) {
        if (!error) {
            connection = new_connection;
            new_connection->receiveMessage();

            TcpConnection::pointer new_connection = TcpConnection::create(io_service);
            acceptor.async_accept(new_connection->socket(),
                                  boost::bind(&LoggerImpl::handleAccept, new_connection,
                                              boost::ref(acceptor),
                                              boost::asio::placeholders::error));
        } else {
            std::cerr << "Accept Error: " << error.message() << std::endl;
        }
    }
}