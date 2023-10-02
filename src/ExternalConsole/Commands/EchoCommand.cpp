//
// Created by Theophilus Homawoo on 01/10/2023.
//

#include "EchoCommand.hpp"

namespace ExternalConsole {
    void EchoCommand::execute(const std::string& args) {
        std::string strippedArgs = args;
        strippedArgs.erase(0, strippedArgs.find_first_not_of(' '));
        std::cout << strippedArgs << std::endl;
    }
} // namespace ExternalConsole