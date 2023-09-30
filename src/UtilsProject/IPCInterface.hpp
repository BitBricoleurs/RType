//
// Created by Theophilus Homawoo on 30/09/2023.
//

#pragma once

#include <string>

namespace DevTools {
    class IPCInterface {
    public:
        virtual ~IPCInterface() {}

        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual void sendCommand(const std::string& cmd) = 0;
        virtual std::string receiveResponse() = 0;
    };
} // namespace DevTools