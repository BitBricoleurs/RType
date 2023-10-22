//
// Created by alexandre on 17/10/23.
//

#include "LoadConfig.hpp"

namespace LoadConfig {

    std::string LoadConfig::getExecutablePath()
    {
    #if defined(_WIN32) || defined(_WIN64)
      return "";
    #elif defined(__APPLE__)
      char path[1024];
      uint32_t size = sizeof(path);
      if (_NSGetExecutablePath(path, &size) == 0) {
        std::string pathStr = std::string(path);
        return (pathStr.substr(0, pathStr.find_last_of("/")) + "/");
      } else {
        return "";
      }
    #else
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if (count < 0 || count >= PATH_MAX) {
            return "";
        }
        result[count] = '\0';
        char* dir = dirname(result);
        if (dir == NULL) {
            return "";
        }
        std::string path = std::string(dir);
        return path + std::string("/");
    #endif
    }

    ConfigData LoadConfig::loadConfig(const std::string& filePath)
    {

        std::string path = getExecutablePath();
        if (path.empty()) {
            path = "./";
        }
        path = path + filePath;
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << path << std::endl;
            throw std::runtime_error("Failed to open config file.");
        }
        nlohmann::json config;
        try {
            file >> config;
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            throw;
        }
        return ConfigData(config);
    }

    ConfigData LoadConfig::loadConfigWithoutPath(const std::string &filePath)
    {
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
        return ConfigData(config);
    }

}
