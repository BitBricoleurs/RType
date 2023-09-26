/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngine
*/

#pragma once

#include "raylib.h"
#include "src/RenderEngine/RenderCompTypes/TextComponent.hpp"
#include "src/RenderEngine/RenderCompTypes/SpriteComponent.hpp"
#include "src/RenderEngine/RenderCompTypes/ParallaxComponent.hpp"
#include "EventHandler.hpp"
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
        void Draw(ParallaxComponent& parallaxComponent);
        void PollEvents(GameEngine::EventHandler& eventHandler);
        void Shutdown();

    private:
        int screenWidth;
        int screenHeight;
        std::unordered_map<std::string, Texture2D> textureCache;
    };
}
