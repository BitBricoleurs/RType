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
#include "KeyMapping.hpp"
#include <vector>
#include <string>

namespace GameEngine {
    class RenderEngine {
    public:
        RenderEngine() = default;
        ~RenderEngine();

        void Initialize(const char* windowTitle);
        void Draw(const TextComponent& textComponent);
        void Draw(const SpriteComponent& spriteComponent);
        void PollEvents(EventHandler& eventHandler);
        void Shutdown();
        void ClearBackgroundRender(Color colosr);

        size_t getScreenWidth();
        size_t getScreenHeight();

    private:
        size_t screenWidth;
        size_t screenHeight;
        std::unordered_map<std::string, Texture2D> textureCache;
        std::string _baseAssetPath;

            std::vector<KeyMapping> keyMappings = {
        { KEY_SPACE, IsKeyPressed, "SPACE_KEY_PRESSED" },
        { KEY_SPACE, IsKeyReleased, "SPACE_KEY_RELEASED" },
        { KEY_UP, IsKeyPressed, "UP_KEY_PRESSED" },
        { KEY_UP, IsKeyReleased, "UP_KEY_RELEASED" },
        { KEY_DOWN, IsKeyPressed, "DOWN_KEY_PRESSED" },
        { KEY_DOWN, IsKeyReleased, "DOWN_KEY_RELEASED" },
        { KEY_LEFT, IsKeyPressed, "LEFT_KEY_PRESSED" },
        { KEY_LEFT, IsKeyReleased, "LEFT_KEY_RELEASED" },
        { KEY_RIGHT, IsKeyPressed, "RIGHT_KEY_PRESSED" },
        { KEY_RIGHT, IsKeyReleased, "RIGHT_KEY_RELEASED" },
        { KEY_ENTER, IsKeyPressed, "ENTER_KEY_PRESSED" },
        {KEY_LEFT_CONTROL, IsKeyPressed, "CONTROL_KEY_PRESSED"},
        {KEY_ESCAPE, IsKeyPressed, "gameEngineStop"},
    };

    };
}
