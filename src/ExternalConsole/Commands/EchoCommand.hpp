//
// Created by Theophilus Homawoo on 01/10/2023.
//

#pragma once

#include "Command.hpp"

namespace ExternalConsole {
    class EchoCommand : public Command {
    public:
        void execute(const std::string& args) override;
    };
} // namespace ExternalConsole
