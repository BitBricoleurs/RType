//
// Created by Theophilus Homawoo on 24/09/2023.
//

#include <iostream>
#include "ComponentsType.hpp"
#include "LayerType.hpp"

namespace GameEngine {
    size_t ComponentsType::componentTypeCounter = 0;
    std::unordered_map<std::string, size_t> ComponentsType::componentTypeMap;

    size_t LayerType::layerTypeCounter = 0;
    std::unordered_map<std::string, size_t> LayerType::layerTypeMap;
}
