#include "ConsoleClient.hpp"

ConsoleClient::ConsoleClient(const std::string& host, const std::string& port)
    : socket(io_service), running(false) {
    connect(host, port);
}

ConsoleClient::~ConsoleClient() {
    stop();
}

void ConsoleClient::connect(const std::string& host, const std::string& port) {
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, port);
    boost::asio::connect(socket, resolver.resolve(query));
}

void ConsoleClient::start() {
    running = true;
    io_thread = std::thread(&ConsoleClient::ioLoop, this);
    input_thread = std::thread(&ConsoleClient::inputLoop, this);
    read();
}

void ConsoleClient::stop() {
    running = false;
    cv.notify_all();
    io_service.stop();
    if (io_thread.joinable()) {
        io_thread.join();
    }
    if (input_thread.joinable()) {
        input_thread.join();
    }
}

void ConsoleClient::read() {
    boost::asio::async_read_until(socket, boost::asio::dynamic_buffer(input_buffer), '\n',
        [this](const boost::system::error_code& error, std::size_t length) {
            if (!error) {
                std::string message = input_buffer.substr(0, length);
                input_buffer.erase(0, length);
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "Received message from server: " << message << std::endl;
                pending_messages.push_back(message);
                cv.notify_all();
                read();
            } else {
                stop();
            }
        }
    );
}

void ConsoleClient::ioLoop() {
    while (running) {
        std::unique_lock<std::mutex> lock(output_mutex);
        cv.wait(lock, [this] { return !running || !pending_messages.empty(); });

        if (!running) {
            break;
        }

        while (!pending_messages.empty()) {
            const auto& message = pending_messages.front();
            std::cout << "\r\033[K" << message;
            if (message.back() != '\n') {
                std::cout << std::endl;
            }
            std::cout << "> " << current_input << std::flush;
            pending_messages.pop_front();
        }
    }
}

void ConsoleClient::inputLoop() {
    while (running) {
        std::string input;
        {
            std::unique_lock<std::mutex> lock(output_mutex);
            std::cout << "> " << std::flush;
        }
        std::getline(std::cin, input);
        if (!running) {
            break;
        }
        {
            std::lock_guard<std::mutex> lock(output_mutex);
            // Do something with the input here
            // For example, send it to the server
            // sendToServer(input + "\n");
            current_input = "";
        }
    }
}
