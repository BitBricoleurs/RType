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


class ConsoleClient : public std::enable_shared_from_this<ConsoleClient> {
public:
    ConsoleClient(boost::asio::io_context& io_service, const std::string& host, const std::string& port);
    ~ConsoleClient();
    void start();
    void stop();

private:
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket;
    boost::asio::strand<boost::asio::io_service::executor_type> strand;
    std::thread io_thread;
    std::string input_data;
    std::string user_input_buffer;
    std::string input_buffer;
    std::mutex input_mutex;
    std::mutex mutex;
    std::thread input_thread;
    bool running;
    std::condition_variable cv;

    void connect(const std::string& host, const std::string& port);
    void start_input_thread();
    void read();
};
