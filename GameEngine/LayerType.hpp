//
// Created by Theophilus Homawoo on 20/09/2023.
//

#pragma once

#include <iostream>
#include <unordered_map>

namespace GameEngine {
    class LayerType {
    public:
        LayerType();
        ~LayerType();

        static size_t getNewLayerType();
        static size_t getNewLayerType(std::string componentName);
        size_t getLayerType(std::string componentName);
    private:
        static size_t layerTypeCounter;
        std::unordered_map<std::string, size_t> layerTypeMap;
    };
} // namespace GameEngine
