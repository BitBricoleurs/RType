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
        SetTargetFPS(60);
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
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

    void RenderEngine::Draw(ParallaxComponent& parallaxComponent) {
        std::string path = parallaxComponent.getImagePath();
        if (parallaxComponent.getOrientation() == 0) {
            parallaxComponent.setX(parallaxComponent.getX() - parallaxComponent.getSpeed());
            if (parallaxComponent.getX() <= -screenWidth)
                parallaxComponent.setX(screenWidth);
        } else {
            parallaxComponent.setY(parallaxComponent.getY() - parallaxComponent.getSpeed());
            if (parallaxComponent.getY() <= -screenHeight)
                parallaxComponent.setY(screenHeight);
        }

        auto it = textureCache.find(path);
        if (it == textureCache.end()) {
            Texture2D texture = LoadTexture(path.c_str());
            textureCache[path] = texture;
        }

        DrawTexture(textureCache[path], parallaxComponent.getX(), parallaxComponent.getY(), RAYWHITE);
    }

void RenderEngine::PollEvents(GameEngine::EventHandler& eventHandler) {
        if (IsKeyPressed(KEY_SPACE))
            eventHandler.queueEvent("SPACE_KEY_PRESSED");
        if (IsKeyPressed(KEY_UP))
            eventHandler.queueEvent("UP_KEY_PRESSED");
        if (IsKeyPressed(KEY_DOWN))
            eventHandler.queueEvent("DOWN_KEY_PRESSED");
        if (IsKeyPressed(KEY_LEFT))
            eventHandler.queueEvent("LEFT_KEY_PRESSED");
        if (IsKeyPressed(KEY_RIGHT))
            eventHandler.queueEvent("RIGHT_KEY_PRESSED");
        if (IsKeyPressed(KEY_ENTER))
            eventHandler.queueEvent("ENTER_KEY_PRESSED");
        if (IsKeyPressed(KEY_ESCAPE))
            eventHandler.queueEvent("ESCAPE_KEY_PRESSED");
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            eventHandler.queueEvent("MouseLeftButtonPressed");
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            eventHandler.queueEvent("MouseRightButtonPressed");
    }

    void RenderEngine::Shutdown() {
        CloseWindow();
    }
}
