/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngine
*/

#include "RenderEngine.hpp"
#include <filesystem>


#if defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#endif

namespace GameEngine {

std::string getExecutablePath() {
#if defined(_WIN32) || defined(_WIN64)
  return "";
#elif defined(__APPLE__)
  char path[1024];
  uint32_t size = sizeof(path);
  if (_NSGetExecutablePath(path, &size) == 0) {
    std::string pathStr = std::string(path);
    return (pathStr.substr(0, pathStr.find_last_of("/")) + "/");
  } else {
    return "";
  }
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count < 0 || count >= PATH_MAX) {
        return "";
    }
    result[count] = '\0';
    char* dir = dirname(result);
    if (dir == NULL) {
        return "";
    }
    std::string path = std::string(dir);
    return path + std::string("/");
#endif
}

RenderEngine::~RenderEngine() {
  for (auto &pair : textureCache) {
    UnloadTexture(pair.second);
  }
}


void RenderEngine::Initialize(const char *windowTitle) {
    InitWindow(0, 0, windowTitle);
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    scaleX = (float)screenWidth / 1920.0f;
    scaleY = (float)screenHeight / 1080.0f;
    _baseAssetPath = getExecutablePath();
    if (_baseAssetPath.empty()) {
        _baseAssetPath = "./";
    }
}

void RenderEngine::Draw(const ButtonComponent &buttonComponent) {
    if (!buttonComponent.isVisible) {
        return;
    }

    ColorR color;
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
    Draw(spriteComponent);
}


void RenderEngine::Draw(const TextComponent &textComponent) {
    Vector2 position = { textComponent.pos.x * scaleX, textComponent.pos.y * scaleY };
    Color color = { textComponent.color.r, textComponent.color.g, textComponent.color.b, textComponent.color.a };

    if (textComponent.isVisible) {
      DrawTextEx(GetFontDefault(), textComponent.text.c_str(), position, textComponent.fontSize, 0, color);
  }
}


void RenderEngine::Draw(const SpriteComponent &spriteComponent) {
    if (spriteComponent.isVisible) {
        std::string path = _baseAssetPath + spriteComponent.imagePath;

        auto it = textureCache.find(path);
        if (it == textureCache.end()) {
            if (fileExists(path)) {
                Texture2D texture = LoadTexture(path.c_str());
                if (texture.id != 0) {
                    textureCache[path] = texture;
                } else {
                    std::cout << "Log: texture not loaded: " << path.c_str() << std::endl;
                    return;
                }
            } else {
                std::cout << "Log: cannot find file: " << path.c_str() << std::endl;
                return;
            }
        }
        DrawTexturePro(textureCache[path],
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


void RenderEngine::PollEvents(GameEngine::EventHandler& eventHandler, std::vector<std::pair<size_t, std::shared_ptr<ButtonComponent>>> buttons) {
    for (const auto& mapping : keyMappings) {
        if (mapping.checkFunction(mapping.key)) {
            eventHandler.queueEvent(mapping.eventName);
        }
    }

    Vector2 mousePosition = GetMousePosition();
    Vect2 mousePos;
    mousePos.x = mousePosition.x;
    mousePos.y = mousePosition.y;

    for (auto [id, button] : buttons) {
      bool isHovering =
          (mousePosition.x >= button->pos.x &&
           mousePosition.x <=
               button->pos.x + button->rect1.w * button->scale) &&
          (mousePosition.y >= button->pos.y &&
           mousePosition.y <= button->pos.y + button->rect1.h * button->scale);

      if (isHovering && button->state != ButtonComponent::HOVER) {
        button->state = ButtonComponent::HOVER;
        eventHandler.queueEvent(button->hoverEvent, id);
      } else if (!isHovering && button->state == ButtonComponent::HOVER) {
        button->state = ButtonComponent::NORMAL;
      }
        if (isHovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            eventHandler.queueEvent(button->clickEvent, id);
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
  
RenderEngine::RenderEngine() {
  // font = LoadFontEx("assets/Onick.ttf", 32, 0, 250);
}

void RenderEngine::Shutdown() { CloseWindow(); }

size_t RenderEngine::getScreenHeight()
{
    return screenHeight;
}

size_t RenderEngine::getScreenWidth()
{
    return screenWidth;
}

} // namespace GameEngine
