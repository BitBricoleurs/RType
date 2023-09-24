/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngine
*/

#pragma once

#include "raylib.h"
#include "RenderCompTypes/TextComponent.hpp"
#include "RenderCompTypes/SpriteComponent.hpp"
#include <unordered_map>
#include <string>

namespace GameEngine {
    class RenderEngine {
    public:
        RenderEngine() = default;
        ~RenderEngine();

        void Initialize(int screenWidth, int screenHeight, const char* windowTitle);
        void Draw(const TextComponent& textComponent);
        void Draw(const SpriteComponent& spriteComponent);
        void Shutdown();

    private:
        std::unordered_map<std::string, Texture2D> textureCache;
    };
}
