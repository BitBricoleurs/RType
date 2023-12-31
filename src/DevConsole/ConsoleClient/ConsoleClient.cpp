#include "ConsoleClient.hpp"
#include <iostream>

ConsoleClient::ConsoleClient(boost::asio::io_context& io_service, const std::string& host, const std::string& port)
    : socket(io_service), strand(io_service.get_executor()), running(false) {
    connect(host, port);
}

ConsoleClient::~ConsoleClient() {
    stop();
}

void ConsoleClient::start() {
    running = true;
    io_thread = std::thread([this] { io_service.run(); });
    start_input_thread();
    read();
}

void ConsoleClient::stop() {
    running = false;
    if (input_thread.joinable()) {
        input_thread.join();
    }
    io_service.stop();
    if (io_thread.joinable()) {
        io_thread.join();
    }
}

void ConsoleClient::connect(const std::string& host, const std::string& port) {
    try {
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(host, port);
        auto endpoint_iterator = resolver.resolve(query);
        boost::asio::connect(socket, endpoint_iterator);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        stop();
    }
}

void ConsoleClient::read() {
    boost::asio::async_read_until(socket, boost::asio::dynamic_buffer(input_buffer), '\n',
        [this](const boost::system::error_code& error, std::size_t length) {
            if (!error) {
                std::string line(input_buffer.substr(0, length));
                input_buffer.erase(0, length);

                std::string user_input_copy;
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    user_input_copy = user_input_buffer;
                }

                std::cout << "\r\033[2K" << line << user_input_copy << std::flush;
                read();
            } else if (error == boost::asio::error::eof) {
                std::cerr << "Connection closed by server." << std::endl;
                stop();
            } else if (error) {
                std::cerr << "Error on receive: " << error.message() << std::endl;
                stop();
            }
        }
    );
}

void ConsoleClient::start_input_thread() {
    input_thread = std::thread([this] {
        while (running) {
            std::string local_input_buffer;
            std::getline(std::cin, local_input_buffer);
            if (!running) break;

            local_input_buffer += '\n';

            {
                std::lock_guard<std::mutex> lock(mutex);
                user_input_buffer = local_input_buffer;
            }

            boost::asio::post(strand, [this, local_input_buffer]() {
                boost::asio::async_write(socket, boost::asio::buffer(local_input_buffer),
                    [this, local_input_buffer](const boost::system::error_code& error, std::size_t /*length*/) {
                        if (error) {
                            stop();
                        } else {
                            {
                                std::lock_guard<std::mutex> lock(mutex);
                                user_input_buffer.clear();
                            }
                        }
                    }
                );
            });

        }
    });
}

