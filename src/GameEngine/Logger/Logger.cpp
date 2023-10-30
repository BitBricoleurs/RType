//
// Created by Theophilus Homawoo on 22/10/2023.
//

#include "Logger.hpp"
#include <ctime>
#include <sstream>
#include <thread>
#include "LoggerImpl.hpp"

namespace GameEngine {
    Logger::LogLevel Logger::currentLogLevel = Logger::LogLevel::INFO;
    bool Logger::wantsToReceiveLogs = false;
    std::unique_ptr<LoggerImpl> Logger::loggerImpl = std::make_unique<LoggerImpl>();

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
        if (wantsToReceiveLogs) {
            loggerImpl->sendLog(full_message);
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
        loggerImpl->startServer(port);
    }


}