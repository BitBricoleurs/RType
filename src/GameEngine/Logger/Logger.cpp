//
// Created by Theophilus Homawoo on 22/10/2023.
//

#include "Logger.hpp"
#include "LoggerImpl.hpp"
#include <ctime>
#include <sstream>
#include <thread>

namespace GameEngine {
    Logger::LogLevel Logger::currentLogLevel = LogLevel::INFO;
    bool Logger::wantsToReceiveLogs = false;

    void Logger::setLogLevel(LogLevel level) {
        currentLogLevel = level;
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
}