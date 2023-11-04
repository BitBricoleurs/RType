//
// Created by Theophilus Homawoo on 22/10/2023.
//

#include "Logger.hpp"
#include "LoggerImpl.hpp"
#include <ctime>
#include <sstream>
#include <thread>

namespace GameEngine {
    int Logger::currentLogLevel = 1;
    bool Logger::wantsToReceiveLogs = false;

    void Logger::setLogLevel(int level) {
        currentLogLevel = level;
    }

    void Logger::info(const std::string& message) {
        log(1, message);
    }

    void Logger::warning(const std::string& message) {
        log(2, message);
    }

    void Logger::error(const std::string& message) {
        log(3, message);
    }

    std::string Logger::levelToString(int level) {
        switch (level) {
            case 1: return "\033[32mINFO\033[0m";
            case 2: return "\033[33mWARNING\033[0m";
            case 3: return "\033[31mERROR\033[0m";
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