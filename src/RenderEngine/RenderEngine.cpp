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

void RenderEngine::Initialize(int screenWidth, int screenHeight,
                              const char *windowTitle) {
  InitWindow(screenWidth, screenHeight, windowTitle);
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
    _baseAssetPath = getExecutablePath();
  if (_baseAssetPath.empty()) {
    _baseAssetPath = "./";
  }
}

void RenderEngine::Draw(const TextComponent &textComponent) {
  DrawText(textComponent.text.c_str(), textComponent.pos.x,
           textComponent.pos.y, textComponent.fontSize,
           {textComponent.color.r, textComponent.color.g,
            textComponent.color.b, textComponent.color.a});
}

void RenderEngine::Draw(const SpriteComponent &spriteComponent) {
        std::string path = _baseAssetPath + spriteComponent.imagePath;
  
        auto it = textureCache.find(path);
        if (it == textureCache.end()) {
            Texture2D texture = LoadTexture(path.c_str());
            textureCache[path] = texture;
        }
        DrawTexturePro(textureCache[path], { spriteComponent.rect1.x, spriteComponent.rect1.y, spriteComponent.rect1.w, spriteComponent.rect1.h }, {spriteComponent.pos.x, spriteComponent.pos.y, spriteComponent.rect1.w * spriteComponent.scale, spriteComponent.rect1.h * spriteComponent.scale}, {spriteComponent.origin.x, spriteComponent.origin.y}, spriteComponent.rotation, {spriteComponent.tint.r, spriteComponent.tint.g, spriteComponent.tint.b, spriteComponent.tint.a});
    }


void RenderEngine::PollEvents(GameEngine::EventHandler& eventHandler) {
        if (IsKeyPressed(KEY_SPACE))
            eventHandler.queueEvent("SPACE_KEY_PRESSED");
        if (IsKeyReleased(KEY_SPACE))
            eventHandler.queueEvent("SPACE_KEY_RELEASED");
        if (IsKeyPressed(KEY_UP))
            eventHandler.queueEvent("UP_KEY_PRESSED");
        if (IsKeyReleased(KEY_UP))
            eventHandler.queueEvent("UP_KEY_RELEASED");
        if (IsKeyPressed(KEY_DOWN))
            eventHandler.queueEvent("DOWN_KEY_PRESSED");
        if (IsKeyReleased(KEY_DOWN))
            eventHandler.queueEvent("DOWN_KEY_RELEASED");
        if (IsKeyPressed(KEY_LEFT))
            eventHandler.queueEvent("LEFT_KEY_PRESSED");
        if (IsKeyReleased(KEY_LEFT))
            eventHandler.queueEvent("LEFT_KEY_RELEASED");
        if (IsKeyPressed(KEY_RIGHT))
            eventHandler.queueEvent("RIGHT_KEY_PRESSED");
        if (IsKeyReleased(KEY_RIGHT))
            eventHandler.queueEvent("RIGHT_KEY_RELEASED");
        if (IsKeyPressed(KEY_ENTER))
            eventHandler.queueEvent("ENTER_KEY_PRESSED");
        if (IsKeyPressed(KEY_ESCAPE))
            eventHandler.queueEvent("ESCAPE_KEY_PRESSED");
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            eventHandler.queueEvent("MouseLeftButtonPressed");
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            eventHandler.queueEvent("MouseRightButtonPressed");
        if (IsKeyPressed(KEY_LEFT_CONTROL)) {
            eventHandler.queueEvent("CONTROL_KEY_PRESSED");
            }
        if (IsKeyReleased(KEY_LEFT_CONTROL))
            eventHandler.queueEvent("CONTROL_KEY_RELEASED");
        if (WindowShouldClose()) {
            eventHandler.queueEvent("gameEngineStop");
        }
}
void RenderEngine::ClearBackgroundRender(Color color) {
  ClearBackground(color);
}

void RenderEngine::Shutdown() { CloseWindow(); }
} // namespace GameEngine
