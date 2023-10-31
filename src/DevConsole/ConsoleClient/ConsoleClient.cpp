#include "ConsoleClient.hpp"
#include <iostream>

#ifdef _WIN32
    ConsoleClient::ConsoleClient(boost::asio::io_context& io_service, const std::string& host, const std::string& port)
        : socket(io_service), strand(io_service.get_executor()), input_descriptor(io_service), running(false) {

        HANDLE stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE duplicateHandle;
        if (!DuplicateHandle(GetCurrentProcess(), stdinHandle, GetCurrentProcess(), &duplicateHandle, 0, TRUE, DUPLICATE_SAME_ACCESS)) {
            throw std::runtime_error("Failed to duplicate standard input handle");
        }

        input_descriptor.assign(duplicateHandle);

        connect(host, port);
    }
#else
    ConsoleClient::ConsoleClient(boost::asio::io_context& io_service, const std::string& host, const std::string& port)
        : socket(io_service), strand(io_service.get_executor()), input_descriptor(io_service, ::dup(STDIN_FILENO)), running(false) {
        connect(host, port);
    }
#endif

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
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, port);
    boost::asio::connect(socket, resolver.resolve(query));
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

                    std::cout << "\r\033[2K"
                              << line
                              << user_input_copy
                              << std::flush;
                    read();
                } else {
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

