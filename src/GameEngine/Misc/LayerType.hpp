//
// Created by Theophilus Homawoo on 20/09/2023.
//

#pragma once

#include <iostream>
#include <unordered_map>

namespace GameEngine {
    class LayerType {
    public:
        LayerType() = default;
        ~LayerType() = default;

        static size_t getNewLayerType() {
            return layerTypeCounter++;
        }

        static size_t getLayerTypeCounter() {
            return layerTypeCounter;
        }

        static size_t getNewLayerType(std::string componentName) {
            return layerTypeMap[componentName] = layerTypeCounter++;
        }

        size_t getLayerType(std::string componentName) {
            return layerTypeMap[componentName];
        }
    private:
        static size_t layerTypeCounter;
        static std::unordered_map<std::string, size_t> layerTypeMap;
    };
} // namespace GameEngine
