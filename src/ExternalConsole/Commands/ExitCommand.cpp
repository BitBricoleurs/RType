//
// Created by Theophilus Homawoo on 01/10/2023.
//

#include "ExitCommand.hpp"

namespace ExternalConsole {
    void ExitCommand::execute(const std::string& args) {
        std::cout << "Exiting..." << std::endl;
        exit(0);
    }
}