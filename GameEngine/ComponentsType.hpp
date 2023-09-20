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

            static size_t getNewComponentType() {
                return componentTypeCounter++;
            }

            static size_t getNewComponentType(std::string componentName) {
                return componentTypeMap[componentName] = componentTypeCounter++;
            }

            size_t getComponentType(std::string componentName) {
                return componentTypeMap[componentName];
            }

        private:
            static size_t componentTypeCounter;
            std::unordered_map<std::string, size_t> componentTypeMap;
    };
} // namespace GameEngine
