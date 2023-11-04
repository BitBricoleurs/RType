//
// Created by Theophilus Homawoo on 28/10/2023.
//

#include "ConsoleClient/ConsoleClient.hpp"
#include <memory>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ConsoleClient <host> <port>\n";
        return 1;
    }

    auto const host = std::string(argv[1]);
    auto const port = std::string(argv[2]);

    boost::asio::io_service io_service;

    try {
        auto client = std::make_shared<ConsoleClient>(io_service, host, port);
        client->start();
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 84;
    }


    return 0;
}

