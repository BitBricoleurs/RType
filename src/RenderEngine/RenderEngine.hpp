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
#include "ButtonComponent.hpp"
#include "EventHandler.hpp"
#include <unordered_map>
#include "KeyMapping.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "LoadConfig.hpp"
#include "ResourceManager.hpp"

namespace RenderEngine {
    class RenderEngine {
    public:
      RenderEngine() = default;
      ~RenderEngine();

      void Initialize(const char *windowTitle);
      void Draw(const TextComponent &textComponent, std::shared_ptr<ResourceManager>& ResourceManager);
      void Draw(const SpriteComponent &spriteComponent, std::shared_ptr<ResourceManager>& ResourceManager);
      void Draw(const ButtonComponent &buttonComponent, std::shared_ptr<ResourceManager>& ResourceManager);
      void PollEvents(
          GameEngine::EventHandler &eventHandler,
          std::vector<std::pair<size_t, ButtonComponent>>
              buttons);
      void Shutdown();
      void ClearBackgroundRender(Color color);
      size_t getScreenWidth() const;
      size_t getScreenHeight() const;

    private:
        size_t screenWidth{};
        size_t screenHeight{};
        std::string _baseAssetPath;
        float scaleX{};
        float scaleY{};


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
        {KEY_F11, IsKeyPressed, "toggleFullScreen"},
    };

    static bool fileExists(const std::string& path);
};
}
