//
// Created by Theophilus Homawoo on 28/10/2023.
//

#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <string>
#include <boost/asio.hpp>

class ConsoleClient {
public:
    ConsoleClient(const std::string& host, const std::string& port);
    ~ConsoleClient();

    void start();
    void stop();

private:
    void connect(const std::string& host, const std::string& port);
    void read();
    void ioLoop();
    void inputLoop();

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket;
    std::thread io_thread, input_thread;
    std::mutex output_mutex;
    std::condition_variable cv;
    std::deque<std::string> pending_messages;
    std::string current_input;
    std::string input_buffer;
    bool running;
};
