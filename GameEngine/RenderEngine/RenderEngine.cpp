/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngine
*/

#include "RenderEngine.hpp"

namespace GameEngine {
    RenderEngine::~RenderEngine() {
        for (auto& pair : textureCache) {
            UnloadTexture(pair.second);
        }
    }

    void RenderEngine::Initialize(int screenWidth, int screenHeight, const char* windowTitle) {
        InitWindow(screenWidth, screenHeight, windowTitle);
    }

    void RenderEngine::Draw(const TextComponent& textComponent) {
        DrawText(textComponent.getText().c_str(), textComponent.getX(), textComponent.getY(), textComponent.getFontSize(), RAYWHITE);
    }

    void RenderEngine::Draw(const SpriteComponent& spriteComponent) {
        std::string path = spriteComponent.getImagePath();

        auto it = textureCache.find(path);
        if (it == textureCache.end()) {
            Texture2D texture = LoadTexture(path.c_str());
            textureCache[path] = texture;
        } 

        DrawTexture(textureCache[path], spriteComponent.getX(), spriteComponent.getY(), RAYWHITE);
    }

    void RenderEngine::Shutdown() {
        CloseWindow();
    }
}
