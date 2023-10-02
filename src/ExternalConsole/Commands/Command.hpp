//
// Created by Theophilus Homawoo on 01/10/2023.
//

#pragma once

#include <iostream>
#include <string>

namespace ExternalConsole {
    class Command {
        public:
            virtual ~Command() {}
            virtual void execute(const std::string& args) = 0;
    };
} // namespace ExternalConsole
