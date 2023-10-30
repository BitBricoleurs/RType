//
// Created by Theophilus Homawoo on 22/10/2023.
//

#pragma once

#include <iostream>
#include <string>

namespace GameEngine {
    class LoggerImpl;
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
        static bool wantsToReceiveLogs;

    private:
        static LogLevel currentLogLevel;
        static std::unique_ptr<LoggerImpl> loggerImpl;
        static std::string levelToString(LogLevel level);
        static std::string getCurrentTimestamp();

    };
}
