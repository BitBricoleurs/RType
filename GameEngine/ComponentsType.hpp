//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <iostream>
#include <unordered_map>


namespace GameEngine {
    class ComponentsType {
        public:
            ComponentsType();
            ~ComponentsType();

            static size_t getNewComponentType();
            static size_t getNewComponentType(std::string componentName);
            size_t getComponentType(std::string componentName);
        private:
            static size_t componentTypeCounter;
            std::unordered_map<std::string, size_t> componentTypeMap;
    };
} // namespace GameEngine
