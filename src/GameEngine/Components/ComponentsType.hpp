//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <iostream>
#include <unordered_map>

namespace GameEngine {
class ComponentsType {
  public:
    ComponentsType() = default;
    ~ComponentsType() = default;

    static size_t getNewComponentType() { return componentTypeCounter++; }

    static size_t getNewComponentType(const std::string& componentName) {
        return componentTypeMap[componentName] = componentTypeCounter++;
    }

    static size_t getComponentType(const std::string& componentName) { return componentTypeMap[componentName]; }

  private:
    static size_t componentTypeCounter;
    static std::unordered_map<std::string, size_t> componentTypeMap;
};
} // namespace GameEngine
