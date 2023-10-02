//
// Created by Bartosz on 9/26/23.
//

#include "ComponentsType.hpp"

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
        return getComponentTypeMap()[componentName];
    }

    size_t& ComponentsType::getComponentTypeCounter() {
        static size_t componentTypeCounter = 0;
        return componentTypeCounter;
    }

    std::unordered_map<std::string, size_t>& ComponentsType::getComponentTypeMap() {
        static std::unordered_map<std::string, size_t> componentTypeMap;
        return componentTypeMap;
    }

} // namespace GameEngine
