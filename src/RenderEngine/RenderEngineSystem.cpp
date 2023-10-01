/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngingeSystem
*/

#include "RenderEngineSystem.hpp"
#include <algorithm>

namespace GameEngine {
    RenderEngineSystem::RenderEngineSystem(int width, int height, const char* windowName, char* argv[]) {
        renderEngine = std::make_shared<RenderEngine>();
        renderEngine->Initialize(width, height, windowName, argv);
    }

    RenderEngineSystem::~RenderEngineSystem() {
        renderEngine->Shutdown();
    }

    void RenderEngineSystem::update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) {

        std::vector<std::optional<std::shared_ptr<IComponent>>> textComponents = componentsContainer.getComponents(ComponentsType::getComponentType("TextComponent"));
        std::vector<std::optional<std::shared_ptr<IComponent>>> spriteComponents = componentsContainer.getComponents(ComponentsType::getComponentType("SpriteComponent"));
        renderEngine->PollEvents(eventHandler);

        std::vector<TextComponent> sortedTextComponents;
        std::vector<SpriteComponent> sortedSpriteComponents;

        for (const auto &component: textComponents) {
            if (component.has_value()) {
                auto text = std::dynamic_pointer_cast<TextComponent>(std::any_cast<std::shared_ptr<IComponent>>(component.value()));
                if (text) {
                    sortedTextComponents.push_back(*text);
                }
            }
        }
        std::sort(sortedTextComponents.begin(), sortedTextComponents.end(),
                  [](const TextComponent &a, const TextComponent &b) {
                      return a.getLayer() < b.getLayer();
                  });

        for (const auto &component: spriteComponents) {
            if (component.has_value()) {
                auto sprite = std::dynamic_pointer_cast<SpriteComponent>(std::any_cast<std::shared_ptr<IComponent>>(component.value()));
                if (sprite) {
                    sortedSpriteComponents.push_back(*sprite);
                }
            }
        }
        std::sort(sortedSpriteComponents.begin(), sortedSpriteComponents.end(),
                  [](const SpriteComponent &a, const SpriteComponent &b) {
                      return a.getLayer() < b.getLayer();
                  });


        renderEngine->ClearBackgroundRender(BLACK);

        BeginDrawing();
        for (const auto &component: sortedTextComponents) {
            renderEngine->Draw(component);
        }

        for (const auto &component: sortedSpriteComponents) {
            renderEngine->Draw(component);
        }

        EndDrawing();


    }

}
