/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngingeSystem
*/

#include "RenderEngineSystem.hpp"
#include <algorithm>

namespace GameEngine {
RenderEngineSystem::RenderEngineSystem(const char *windowName)
{
    renderEngine = std::make_unique<RenderEngine>();
    renderEngine->Initialize(windowName);
}

RenderEngineSystem::~RenderEngineSystem() { renderEngine->Shutdown(); }

void RenderEngineSystem::update(ComponentsContainer &componentsContainer,
                                EventHandler &eventHandler) {

  std::vector<std::optional<std::shared_ptr<IComponent>>> textComponents =
      componentsContainer.getComponents(
          ComponentsType::getComponentType("TextComponent"));
  std::vector<std::optional<std::shared_ptr<IComponent>>> spriteComponents =
      componentsContainer.getComponents(
          ComponentsType::getComponentType("SpriteComponent"));
  std::vector<std::optional<std::shared_ptr<IComponent>>> buttonComponents =
      componentsContainer.getComponents(
          ComponentsType::getComponentType("ButtonComponent"));

  std::vector<std::shared_ptr<ButtonComponent>> sortedButtonComponents;

  for (const auto &component : buttonComponents) {
    if (component.has_value()) {
      auto button = std::dynamic_pointer_cast<ButtonComponent>(component.value());
        sortedButtonComponents.push_back(button);
    }
    }

  std::stable_sort(sortedButtonComponents.begin(), sortedButtonComponents.end(),
    [](const std::shared_ptr<ButtonComponent> &a, const std::shared_ptr<ButtonComponent> &b) {
        if(a->layer == b->layer) {
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
          std::any_cast<std::shared_ptr<IComponent>>(component.value()));
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
          std::any_cast<std::shared_ptr<IComponent>>(component.value()));
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
    renderEngine->Draw(*component);
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
