//
// Created by Bartosz on 10/25/23.
//

#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>


class ResourceManager {
public:
    ResourceManager() = default;

    Texture2D LoadTexture(const std::string& fileName) {
        if (textures.find(fileName) != textures.end()) {
            return textures[fileName];
        }
        Texture2D texture = ::LoadTexture(fileName.c_str());
        textures[fileName] = texture;
        return texture;
    }

    void UnloadTexture(const std::string& fileName) {
        auto it = textures.find(fileName);
        if (it != textures.end()) {
            ::UnloadTexture(it->second);
            textures.erase(it);
        }
    }

    void PreloadTexture(const std::string& fileName) {
        LoadTexture(fileName);
    }

    void ClearAllTextures() {
        for (auto& texture : textures) {
            UnloadTexture(texture.first);
        }
        textures.clear();
    }

private:
    std::unordered_map<std::string, Texture2D> textures;
};
