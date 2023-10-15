/*
** EPITECH PROJECT, 2023
** RType
** File description:
** LoadConfig
*/

#include "EntityFactory.hpp"

nlohmann::json EntityFactory::loadConfig(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        throw std::runtime_error("Failed to open config file.");
    }
    nlohmann::json config;
    try {
        file >> config;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        throw;
    }
    return config;
}
