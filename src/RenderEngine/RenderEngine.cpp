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
        BeginDrawing();
        DrawText(textComponent.getText().c_str(), textComponent.getX(), textComponent.getY(), textComponent.getFontSize(), BLACK);
        EndDrawing();
    }

    void RenderEngine::Draw(const SpriteComponent& spriteComponent) {
        BeginDrawing();

        std::string path = spriteComponent.getImagePath();

        auto it = textureCache.find(path);
        if (it == textureCache.end()) {
            Texture2D texture = LoadTexture(path.c_str());
            textureCache[path] = texture;
        }

        // Convert GameEngine::Rectangle and Vector2 to Raylib's Rectangle and Vector2
        rect gameRect = spriteComponent.getRect();
        ::Rectangle raylibRect = { gameRect.x, gameRect.y, gameRect.width, gameRect.height };

        GameEngine::Vector2 gamePos = spriteComponent.getPos();
        ::Vector2 raylibPos = { gamePos.x, gamePos.y };

        DrawTextureRec(textureCache[path], raylibRect, raylibPos, RAYWHITE);

        EndDrawing();
    }

    void RenderEngine::Draw(ParallaxComponent& parallaxComponent) {
        BeginDrawing();

        std::string path = parallaxComponent.getImagePath();
        GameEngine::Vector2 gamePos = parallaxComponent.getPos();

        if (parallaxComponent.getOrientation() == 0) {
            gamePos.x -= parallaxComponent.getSpeed();
            if (gamePos.x <= -screenWidth)
                gamePos.x = screenWidth;
        } else {
            gamePos.y -= parallaxComponent.getSpeed();
            if (gamePos.y <= -screenHeight)
                gamePos.y = screenHeight;
        }

        parallaxComponent.setPos(gamePos);

        auto it = textureCache.find(path);
        if (it == textureCache.end()) {
            Texture2D texture = LoadTexture(path.c_str());
            textureCache[path] = texture;
        }

        ::Vector2 raylibPos = { gamePos.x, gamePos.y };

        DrawTextureRec(textureCache[path], {0, 0, static_cast<float>(textureCache[path].width), static_cast<float>(textureCache[path].height)}, raylibPos, RAYWHITE);

        EndDrawing();
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
        if (IsKeyReleased(KEY_SPACE))
            eventHandler.queueEvent("SPACE_KEY_RELEASED");
    }

    void RenderEngine::Shutdown() {
        CloseWindow();
    }
}
