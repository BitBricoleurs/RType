//
// Created by alexandre on 17/10/23.
//

#include "ConfigData.hpp"

namespace LoadConfig {

    std::string ConfigData::getString(const std::string& keyPath) const {
        nlohmann::json::json_pointer ptr(keyPath);
        if (data.contains(ptr) && data[ptr].is_string()) {
            return data[ptr].get<std::string>();
        }
        throw std::runtime_error("Key not found or value is not a string: " + keyPath);
    }

    int ConfigData::getInt(const std::string& keyPath) const {
        nlohmann::json::json_pointer ptr(keyPath);
        if (data.contains(ptr) && data[ptr].is_number_integer()) {
            return data[ptr].get<int>();
        }
        throw std::runtime_error("Key not found or value is not an integer: " + keyPath);
    }

    bool ConfigData::getBool(const std::string& keyPath) const {
        nlohmann::json::json_pointer ptr(keyPath);
        if (data.contains(ptr) && data[ptr].is_boolean()) {
            return data[ptr].get<bool>();
        }
        throw std::runtime_error("Key not found or value is not a boolean: " + keyPath);
    }

    float ConfigData::getFloat(const std::string& keyPath) const {
        nlohmann::json::json_pointer ptr(keyPath);
        if (data.contains(ptr) && data[ptr].is_number_float()) {
            return data[ptr].get<float>();
        }
        throw std::runtime_error("Key not found or value is not a float: " + keyPath);
    }

    int ConfigData::getSize(const std::string& keyPath) const {
        nlohmann::json::json_pointer ptr(keyPath);
        if (data.contains(ptr) && data[ptr].is_array()) {
            return data[ptr].size();
        }
        throw std::runtime_error("Key not found or value is not an array: " + keyPath);
    }

    bool ConfigData::keyExists(const std::string& keyPath) const {
        nlohmann::json::json_pointer ptr(keyPath);
        if (data.contains(ptr)) {
            return true;
        }
        return false;
    }

    void ConfigData::eraseKey(const std::string& keyPath, int index) {
        nlohmann::json::json_pointer ptr(keyPath);
        if (data.contains(ptr) && data[ptr].is_array() && index < data[ptr].size()) {
            data[ptr].erase(data[ptr].begin() + index);
            return;
        }
        throw std::runtime_error("Key not found, value is not an array, or index out of bounds: " + keyPath + "[" + std::to_string(index) + "]");
    }

}