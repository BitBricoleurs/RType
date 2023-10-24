/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngingeSystem
*/

#include "RenderEngineSystem.hpp"
#include <algorithm>

namespace RenderEngine {

    RenderEngineSystem::RenderEngineSystem(const char *windowName)
    {
        renderEngine = std::make_unique<RenderEngine>();
        renderEngine->Initialize(windowName);
    }

    RenderEngineSystem::~RenderEngineSystem() { renderEngine->Shutdown(); }

    void RenderEngineSystem::update(GameEngine::ComponentsContainer &componentsContainer,
                                    GameEngine::EventHandler &eventHandler) {

      std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>>
          textComponents = componentsContainer.getComponents(
              GameEngine::ComponentsType::getComponentType("TextComponent"));
      std::vector<std::optional<std::shared_ptr<GameEngine::IComponent>>>
          spriteComponents = componentsContainer.getComponents(
              GameEngine::ComponentsType::getComponentType("SpriteComponent"));

      std::vector<size_t> buttonsIDS =
          componentsContainer.getEntitiesWithComponent(
              GameEngine::ComponentsType::getComponentType("ButtonComponent"));

      std::vector<std::pair<size_t, std::shared_ptr<ButtonComponent>>>
          sortedButtonComponents;

      for (auto id : buttonsIDS) {
        auto button = std::dynamic_pointer_cast<ButtonComponent>(
            std::any_cast<std::shared_ptr<GameEngine::IComponent>>(
                componentsContainer
                    .getComponent(id,
                                  GameEngine::ComponentsType::getComponentType(
                                      "ButtonComponent"))
                    .value()));
        sortedButtonComponents.push_back(std::make_pair(id, button));
      }

  std::stable_sort(sortedButtonComponents.begin(), sortedButtonComponents.end(),
    [](const std::pair<size_t, std::shared_ptr<ButtonComponent>>& p1,
       const std::pair<size_t, std::shared_ptr<ButtonComponent>>& p2) {
        const auto& a = p1.second;
        const auto& b = p2.second;

        if (a->layer == b->layer) {
            return a->pos.x < b->pos.x;
        }
        return a->layer < b->layer;
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

      BeginDrawing();

      for (const auto &component : sortedSpriteComponents) {
        renderEngine->Draw(component);
      }

      for (const auto &component : sortedTextComponents) {
        renderEngine->Draw(component);
      }

  for (const auto &component : sortedButtonComponents) {
    renderEngine->Draw(*component.second);
  }





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
