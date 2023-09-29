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
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
    }

    void RenderEngine::Draw(const TextComponent& textComponent) {
        DrawText(textComponent.getText().c_str(), textComponent.getPos().x, textComponent.getPos().y, textComponent.getFontSize(), {textComponent.getColor().r, textComponent.getColor().g, textComponent.getColor().b, textComponent.getColor().a} );
    }

    void RenderEngine::Draw(const SpriteComponent& spriteComponent) {
        std::string path = spriteComponent.getImagePath();

        auto it = textureCache.find(path);
        if (it == textureCache.end()) {
            Texture2D texture = LoadTexture(path.c_str());
            textureCache[path] = texture;
        }

        DrawTextureRec(textureCache[path], { spriteComponent.getRect().x, spriteComponent.getRect().y, spriteComponent.getRect().width, spriteComponent.getRect().height }, { spriteComponent.getPos().x, spriteComponent.getPos().y }, RAYWHITE);
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

    void RenderEngine::ClearBackgroundRender(Color color) {
        ClearBackground(color);
    }

    void RenderEngine::Shutdown() {
        CloseWindow();
    }
}
