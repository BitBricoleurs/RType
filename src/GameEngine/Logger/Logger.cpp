//
// Created by Theophilus Homawoo on 22/10/2023.
//

#include "Logger.hpp"
#include <ctime>
#include <sstream>
#include <thread>
#include <boost/bind/bind.hpp>


namespace GameEngine {
    Logger::LogLevel Logger::currentLogLevel = Logger::LogLevel::INFO;
    GameEngine::TcpConnection::pointer Logger::connection;
    boost::asio::io_service Logger::io_service;

    void Logger::setLogLevel(Logger::LogLevel level) {
        currentLogLevel = level;
    }

    void Logger::log(LogLevel level, const std::string& message) {
        if (static_cast<int>(level) < static_cast<int>(currentLogLevel)) {
            return;
        }
        std::string log_level_str = levelToString(level);
        std::string timestamp = getCurrentTimestamp();
        std::string full_message = "[" + timestamp + "] [" + log_level_str + "] " + message + "\n";
        if (connection) {
            std::cout << "Sending log to client:" << std::endl;
            connection->sendLog(full_message);
        } else {
            std::cout << full_message;
        }
    }

    void Logger::info(const std::string& message) {
        log(LogLevel::INFO, message);
    }

    void Logger::warning(const std::string& message) {
        log(LogLevel::WARNING, message);
    }

    void Logger::error(const std::string& message) {
        log(LogLevel::ERROR, message);
    }

    std::string Logger::levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::INFO: return "\033[32mINFO\033[0m";
            case LogLevel::WARNING: return "\033[33mWARNING\033[0m";
            case LogLevel::ERROR: return "\033[31mERROR\033[0m";
            default: return "UNKNOWN";
        }
    }



    std::string Logger::getCurrentTimestamp() {
        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
        return buffer;
    }

    void Logger::startServer(unsigned short port) {
        try {
            boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
            while (true) {
                TcpConnection::pointer new_connection = TcpConnection::create(io_service);
                acceptor.accept(new_connection->socket());
                connection = new_connection;
            }
        } catch (std::exception& e) {
            std::cerr << "Server Error: " << e.what() << std::endl;
        }
    }
}

