/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngine
*/

#pragma once

#include "raylib.h"
#include "TextComponent.hpp"
#include "SpriteComponent.hpp"
#include "EventHandler.hpp"
#include <unordered_map>
#include <string>

namespace GameEngine {
    class RenderEngine {
    public:
        RenderEngine();
        ~RenderEngine();

        void Initialize(int screenWidth, int screenHeight, const char* windowTitle);
        void Draw(const TextComponent& textComponent);
        void Draw(const SpriteComponent& spriteComponent);
        void PollEvents(EventHandler& eventHandler);
        void Shutdown();
        void ClearBackgroundRender(Color colosr);

    private:
        int screenWidth;
        int screenHeight;
        std::unordered_map<std::string, Texture2D> textureCache;
        std::string _baseAssetPath;
        Font font;
    };
}
