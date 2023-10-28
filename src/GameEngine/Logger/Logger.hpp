//
// Created by Theophilus Homawoo on 22/10/2023.
//

#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "TcpConnection.hpp"


namespace GameEngine {
    class Logger {
    public:
        enum class LogLevel {
            INFO,
            WARNING,
            ERROR
        };

        static void setLogLevel(LogLevel level);
        static void log(LogLevel level, const std::string& message);
        static void info(const std::string& message);
        static void warning(const std::string& message);
        static void error(const std::string& message);
        static void startServer(unsigned short port);

    private:
        static LogLevel currentLogLevel;
        static TcpConnection::pointer connection;
        static boost::asio::io_service io_service;
        static std::string levelToString(LogLevel level);
        static std::string getCurrentTimestamp();
    };
}
