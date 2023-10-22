//
// Created by Theophilus Homawoo on 22/10/2023.
//

#include "Logger.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

Logger::LogLevel Logger::currentLogLevel = Logger::LogLevel::INFO;

void Logger::setLogLevel(Logger::LogLevel level) {
    currentLogLevel = level;
}

void Logger::log(LogLevel level, const std::string& message) {
    if (static_cast<int>(level) < static_cast<int>(currentLogLevel)) {
        return;  // Skip messages below the current log level
    }
    std::string log_level_str = levelToString(level);
    std::string timestamp = getCurrentTimestamp();
    std::cout << "[" << timestamp << "] [" << log_level_str << "] " << message << std::endl;
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
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
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


