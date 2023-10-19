//
// Created by alexandre on 17/10/23.
//

#pragma once

#include "ConfigData.hpp"
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <libgen.h>
#include <climits>
#include <unistd.h>
#endif

namespace LoadConfig {

    class LoadConfig {
    public:
        static LoadConfig& getInstance() {
            static LoadConfig instance;
            return instance;
        }

        ConfigData loadConfig(const std::string& filePath);
        ConfigData loadConfigWithoutPath(const std::string& filePath);
        std::string getExecutablePath();

        LoadConfig(const LoadConfig&) = delete;
        LoadConfig& operator=(const LoadConfig&) = delete;

    private:
        LoadConfig() = default;
        ~LoadConfig() = default;

    };
}
