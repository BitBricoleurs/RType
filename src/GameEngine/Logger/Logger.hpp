//
// Created by Theophilus Homawoo on 22/10/2023.
//

#pragma once

#include <iostream>
#include <string>

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

private:
    static LogLevel currentLogLevel;
    static std::string levelToString(LogLevel level);
    static std::string getCurrentTimestamp();
};
