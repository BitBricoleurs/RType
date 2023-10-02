//
// Created by Theophilus Homawoo on 01/10/2023.
//

#pragma once

#include "Command.hpp"
#include "map"
#include "/usr/local/include/asio.hpp"

namespace ExternalConsole {
    class Terminal {
    public:
        Terminal();
        ~Terminal();

        void run();
    private:
        void execute(const std::string& command, const std::string& args);
        std::map<std::string, std::unique_ptr<Command>> commands;
        asio::io_context io_context;
        asio::ip::tcp::socket socket;

        void readFromServer();
    };
} // namespace ExternalConsole

