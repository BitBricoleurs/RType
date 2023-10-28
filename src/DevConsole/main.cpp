//
// Created by Theophilus Homawoo on 28/10/2023.
//

#include "ConsoleClient/ConsoleClient.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ConsoleClient <host> <port>" << std::endl;
        return 84;
    }
    if (std::string(argv[2]).find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Port must be a number" << std::endl;
        return 84;
    }

    ConsoleClient client(argv[1], argv[2]);
    client.start();
    while (true) {}
    return 0;
}