//
// Created by Theophilus Homawoo on 01/10/2023.
//

#include "Terminal.hpp"

#include "EchoCommand.hpp"
#include "ExitCommand.hpp"

namespace ExternalConsole {
    Terminal::Terminal() : socket(io_context){
        commands["echo"] = std::make_unique<EchoCommand>();
        commands["exit"] = std::make_unique<ExitCommand>();

        asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "12345");
        asio::connect(socket, endpoints);
    }

    Terminal::~Terminal() {
        socket.close();
    }

    void Terminal::run() {
        std::string command;
        std::string args;

        while (true) {
            std::cout << ">> ";
            std::cin >> command;
            std::getline(std::cin, args);

            execute(command, args);
            readFromServer();
        }
    }

    void Terminal::execute(const std::string& command, const std::string& args) {
        if (commands.find(command) != commands.end()) {
            commands[command]->execute(args);
        } else {
            asio::write(socket, asio::buffer(command + " " + args + "\n"));
        }
    }

    void Terminal::readFromServer() {
        asio::streambuf buffer;
        asio::read_until(socket, buffer, '\n');
        std::string message;
        std::istream input_stream(&buffer);
        std::getline(input_stream, message);
        std::cout << message << std::endl;
    }
} // namespace ExternalConsole