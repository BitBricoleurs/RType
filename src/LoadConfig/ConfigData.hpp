//
// Created by alexandre on 17/10/23.
//

#pragma once
#include <string>
#include <fstream>
#include <optional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <utility>

namespace LoadConfig {
    class ConfigData {
    public:

        explicit ConfigData(nlohmann::json jsonData) : data(std::move(jsonData)) {}

        [[nodiscard]] std::string getString(const std::string& keyPath) const;
        [[nodiscard]] int getInt(const std::string& keyPath) const;
        [[nodiscard]] bool getBool(const std::string& keyPath) const;
        [[nodiscard]] float getFloat(const std::string& keyPath) const;
        void eraseKey(const std::string& keyPath, int index);
        [[nodiscard]] bool keyExists(const std::string& keyPath) const;
        [[nodiscard]] int getSize(const std::string& keyPath) const;

    private:
        nlohmann::json data;
    };
}