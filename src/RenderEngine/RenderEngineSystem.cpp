/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngingeSystem
*/

#include "RenderEngineSystem.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <variant>

namespace RenderEngine {

    RenderEngineSystem::RenderEngineSystem(const char *windowName)
    {
        renderEngine = std::make_unique<RenderEngine>();
        renderEngine->Initialize(windowName);
    }

    RenderEngineSystem::~RenderEngineSystem() { renderEngine->Shutdown(); }

    void RenderEngineSystem::update(GameEngine::ComponentsContainer &componentsContainer,
                                    GameEngine::EventHandler &eventHandler) {

      std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>> textComponents =
          componentsContainer.getComponents(
              GameEngine::ComponentsType::getComponentType("TextComponent"));
      std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>> spriteComponents =
          componentsContainer.getComponents(
              GameEngine::ComponentsType::getComponentType("SpriteComponent"));
      std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>> buttonComponents =
          componentsContainer.getComponents(
              GameEngine::ComponentsType::getComponentType("ButtonComponent"));

      std::vector<ButtonComponent> sortedButtonComponents;

      for (const auto &component : buttonComponents) {
        if (component.has_value()) {
          auto button = std::dynamic_pointer_cast<ButtonComponent>(component.value());
            sortedButtonComponents.push_back(*button);
        }
        }

        std::stable_sort(sortedButtonComponents.begin(), sortedButtonComponents.end(),
            [](const ButtonComponent &a, const ButtonComponent &b) {
                if(a.layer == b.layer) {
                    return a.pos.x < b.pos.x;
                }
                return a.layer < b.layer;
            });

      renderEngine->PollEvents(eventHandler, sortedButtonComponents);

      std::vector<TextComponent> sortedTextComponents;
      std::vector<SpriteComponent> sortedSpriteComponents;

      for (const auto &component : textComponents) {
        if (component.has_value()) {
          auto text = std::dynamic_pointer_cast<TextComponent>(
              std::any_cast<std::shared_ptr<GameEngine::IComponent>>(component.value()));
          if (text) {
            sortedTextComponents.push_back(*text);
          }
        }
      }
      std::stable_sort(sortedTextComponents.begin(), sortedTextComponents.end(),
        [](const TextComponent &a, const TextComponent &b) {
            if(a.layer == b.layer) {
                return a.pos.x < b.pos.x;
            }
            return a.layer < b.layer;
        });

      for (const auto &component : spriteComponents) {
        if (component.has_value()) {
          auto sprite = std::dynamic_pointer_cast<SpriteComponent>(
              std::any_cast<std::shared_ptr<GameEngine::IComponent>>(component.value()));
          if (sprite) {
            sortedSpriteComponents.push_back(*sprite);
          }
        }
      }
      std::stable_sort(sortedSpriteComponents.begin(), sortedSpriteComponents.end(),
        [](const SpriteComponent &a, const SpriteComponent &b) {
            if(a.layer == b.layer) {
                return a.pos.x < b.pos.x;
            }
            return a.layer < b.layer;
        });


      renderEngine->ClearBackgroundRender(BLACK);
      auto windowID = componentsContainer.getComponents(
            GameEngine::ComponentsType::getComponentType("WindowInfoComponent"));
       auto windowcast = std::dynamic_pointer_cast<WindowInfoComponent>(windowID[0].value());
      BeginDrawing();
      BeginMode2D(windowcast->camera);

    std::multimap<size_t, std::variant<SpriteComponent, TextComponent, ButtonComponent>> drawMap;

        for (const auto &sprite : sortedSpriteComponents) {
            drawMap.emplace(sprite.layer, sprite);
        }

        for (const auto &text : sortedTextComponents) {
            drawMap.emplace(text.layer, text);
        }

        for (const auto &button : sortedButtonComponents) {
            drawMap.emplace(button.layer, button);
        }

        for (const auto &[layer, component] : drawMap) {
            std::visit([this](auto&& arg) {
                renderEngine->Draw(arg);
            }, component);
        }
        EndMode2D();
        EndDrawing();
    }
    size_t RenderEngineSystem::getScreenHeight()
    {
        return renderEngine->getScreenHeight();
    }

    size_t RenderEngineSystem::getScreenWidth()
    {
        return renderEngine->getScreenWidth();
    }

} // namespace GameEngine
