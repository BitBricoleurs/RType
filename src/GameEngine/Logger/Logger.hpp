//
// Created by Theophilus Homawoo on 22/10/2023.
//

#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace GameEngine {
    class Logger {
    public:
        static void setLogLevel(int level);
        static void log(int level, const std::string& message);
        static void info(const std::string& message);
        static void warning(const std::string& message);
        static void error(const std::string& message);
        static void startServer(unsigned short port);
        static void stopServer();
        static bool wantsToReceiveLogs;
        struct LoggerImpl;

    private:
        static std::unique_ptr<LoggerImpl> pimpl;
        static int currentLogLevel;
        static std::string levelToString(int level);
        static std::string getCurrentTimestamp();
    };

}
