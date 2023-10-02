//
// Created by Theophilus Homawoo on 01/10/2023.
//

#pragma once

#include "/usr/local/include/asio.hpp"
#include <thread>
#include <memory>
#include <string>
#include <iostream>

namespace GameEngine {

    class GameEngine;
    class SocketServer {
        public:
            SocketServer();
            ~SocketServer();
            void run();
            void stop();
        private:
            asio::io_service io_service;
            asio::ip::tcp::acceptor acceptor;
            std::shared_ptr<asio::ip::tcp::socket> socket;
            void startAccept();
            void handleAccept(std::shared_ptr<asio::ip::tcp::socket> socket, const asio::error_code& error);
            void respond(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& message);
            void awaitCommands(std::shared_ptr<asio::ip::tcp::socket> socket);
    };
}