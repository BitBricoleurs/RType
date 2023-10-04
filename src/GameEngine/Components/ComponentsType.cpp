//
// Created by Bartosz on 9/26/23.
//

#include "ComponentsType.hpp"
#include <iostream>

namespace GameEngine {

    ComponentsType::ComponentsType() = default;
    ComponentsType::~ComponentsType() = default;

    size_t ComponentsType::getNewComponentType() {
        return getComponentTypeCounter()++;
    }

    size_t ComponentsType::getNewComponentType(const std::string& componentName) {
        if (getComponentTypeMap().find(componentName) != getComponentTypeMap().end())
            return getComponentTypeMap()[componentName];
        return getComponentTypeMap()[componentName] = getComponentTypeCounter()++;
    }

    size_t ComponentsType::getComponentType(const std::string& componentName) {
        const auto& map = getComponentTypeMap();
        if (map.find(componentName) == map.end()) {
            return 0;
        }
        return map.at(componentName);
    }
    size_t& ComponentsType::getComponentTypeCounter() {
        static size_t componentTypeCounter = 1;
        return componentTypeCounter;
    }

    std::unordered_map<std::string, size_t>& ComponentsType::getComponentTypeMap() {
        static std::unordered_map<std::string, size_t> componentTypeMap;
        return componentTypeMap;
    }

    std::string ComponentsType::getComponentName(size_t typeId) {
        for (const auto& pair : getComponentTypeMap()) {
            if (pair.second == typeId) {
                return pair.first;
            }
        }
        return "";
    }

} // namespace GameEngine
