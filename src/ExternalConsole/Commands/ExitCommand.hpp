//
// Created by Theophilus Homawoo on 01/10/2023.
//

#include "Command.hpp"

namespace ExternalConsole {
    class ExitCommand : public Command {
    public:
        void execute(const std::string& args) override;
    };
} // namespace ExternalConsole
