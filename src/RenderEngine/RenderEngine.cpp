/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngine
*/

#include "RenderEngine.hpp"
#include "ColorR.hpp"
#include <filesystem>

namespace RenderEngine {
    RenderEngine::~RenderEngine() {}


    void RenderEngine::Initialize(const char *windowTitle) {
        InitWindow(0, 0, windowTitle);
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        scaleX = (float)screenWidth / 1920.0f;
        scaleY = (float)screenHeight / 1080.0f;
        _baseAssetPath = LoadConfig::LoadConfig::getInstance().getExecutablePath();
        if (_baseAssetPath.empty()) {
            _baseAssetPath = "./";
        }
    }

    void RenderEngine::Draw(const ButtonComponent &buttonComponent, std::shared_ptr<ResourceManager>& ResourceManager) {
        if (!buttonComponent.isVisible) {
            return;
        }

        Utils::ColorR color;
        switch (buttonComponent.state) {
            case ButtonComponent::NORMAL:
                color = buttonComponent.tint;
                break;
            case ButtonComponent::HOVER:
                color = buttonComponent.hoverColor;
                break;
            case ButtonComponent::DISABLED:
                color = { 128, 128, 128, 255 };
                break;
        }

        SpriteComponent spriteComponent = static_cast<SpriteComponent>(buttonComponent);
        spriteComponent.tint = color;
        Draw(spriteComponent, ResourceManager);
    }


    void RenderEngine::Draw(const TextComponent &textComponent, std::shared_ptr<ResourceManager>& ResourceManager) {
        Vector2 position = { textComponent.pos.x * scaleX, textComponent.pos.y * scaleY };
        Color color = { textComponent.color.r, textComponent.color.g, textComponent.color.b, textComponent.color.a };

        if (textComponent.isVisible) {
          DrawTextEx(GetFontDefault(), textComponent.text.c_str(), position, textComponent.fontSize, 0, color);
      }
    }


    void RenderEngine::Draw(const SpriteComponent &spriteComponent, std::shared_ptr<ResourceManager>& resourceManager) {
    if (spriteComponent.isVisible) {
        std::string path = _baseAssetPath + spriteComponent.imagePath;
        Texture2D texture = resourceManager->LoadTexture(path);

        if (texture.id == 0) {
            std::cerr << "Log: Failed to load texture: " << path << std::endl;
            return;
        }
        DrawTexturePro(texture,
                       { spriteComponent.rect1.x, spriteComponent.rect1.y, spriteComponent.rect1.w, spriteComponent.rect1.h },
                       {spriteComponent.pos.x * scaleX, spriteComponent.pos.y * scaleY, spriteComponent.rect1.w * spriteComponent.scale * scaleX, spriteComponent.rect1.h * spriteComponent.scale * scaleY},
                       {spriteComponent.origin.x * scaleX, spriteComponent.origin.y * scaleY},
                       spriteComponent.rotation,
                       {spriteComponent.tint.r, spriteComponent.tint.g, spriteComponent.tint.b, spriteComponent.tint.a});
    }
}


    bool RenderEngine::fileExists(const std::string& path) {
        std::ifstream file(path.c_str());
        return file.good();
    }


void RenderEngine::PollEvents(GameEngine::EventHandler& eventHandler, std::vector<std::pair<size_t, ButtonComponent>> buttons) {
    for (const auto& mapping : keyMappings) {
        if (mapping.checkFunction(mapping.key)) {
            eventHandler.queueEvent(mapping.eventName);
        }
    }

        Vector2 mousePosition = GetMousePosition();
        Utils::Vect2 mousePos;
        mousePos.x = mousePosition.x;
        mousePos.y = mousePosition.y;

    for (auto [id, button] : buttons) {
      bool isHovering =
          (mousePosition.x >= button.pos.x * scaleX &&
           mousePosition.x <= button.pos.x * scaleX +
                                  button.rect1.w * button.scale * scaleX) &&
          (mousePosition.y >= button.pos.y * scaleY &&
           mousePosition.y <= button.pos.y * scaleY +
                                  button.rect1.h * button.scale * scaleY);

      if (isHovering && button.state != ButtonComponent::HOVER) {
        button.state = ButtonComponent::HOVER;
        eventHandler.queueEvent(button.hoverEvent, id);
      } else if (!isHovering && button.state == ButtonComponent::HOVER) {
        button.state = ButtonComponent::NORMAL;
      }
        if (isHovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            eventHandler.queueEvent(button.clickEvent, id);
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        eventHandler.queueEvent("MouseLeftButtonPressed", mousePos);
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        eventHandler.queueEvent("MouseRightButtonPressed", mousePos);
    if (WindowShouldClose()) {
        eventHandler.queueEvent("gameEngineStop");
    }
}


    void RenderEngine::ClearBackgroundRender(Color color) {
      ClearBackground(color);
    }

    void RenderEngine::Shutdown() { CloseWindow(); }

    size_t RenderEngine::getScreenHeight() const
    {
        return screenHeight;
    }

    size_t RenderEngine::getScreenWidth() const
    {
        return screenWidth;
    }

} // namespace GameEngine
