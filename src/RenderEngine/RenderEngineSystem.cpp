/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngingeSystem
*/

#include "RenderEngineSystem.hpp"
#include <algorithm>

namespace GameEngine {

    size_t& spriteComponentType() {
        static size_t type = ComponentsType::getNewComponentType("SpriteComponent");
        return type;
    }

    size_t& textComponentType() {
        static size_t type = ComponentsType::getNewComponentType("TextComponent");
        return type;
    }

    size_t& parallaxComponentType() {
        static size_t type = ComponentsType::getNewComponentType("ParallaxComponent");
        return type;
    }

    size_t& audioComponentType() {
        static size_t type = ComponentsType::getNewComponentType("AudioComponentType");
        return type;
    }

    RenderEngineSystem::RenderEngineSystem(int width, int height, const char* windowName) {
        renderEngine = std::make_shared<RenderEngine>();
        renderEngine->Initialize(width, height, windowName);
    }

    RenderEngineSystem::~RenderEngineSystem() {
        renderEngine->Shutdown();
    }

    void RenderEngineSystem::update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) {
        std::vector<std::optional<std::shared_ptr<IComponent>>> textComponents = componentsContainer.getComponents(textComponentType());
        std::vector<std::optional<std::shared_ptr<IComponent>>> spriteComponents = componentsContainer.getComponents(spriteComponentType());
        std::vector<std::optional<std::shared_ptr<IComponent>>> parallaxComponents = componentsContainer.getComponents(parallaxComponentType());
        renderEngine->PollEvents(eventHandler);

        auto sortAndDrawText = [this](std::vector<std::optional<std::shared_ptr<IComponent>>> &components) {
            std::vector<TextComponent> sortedComponents;
            for (const auto &component: components) {
                if (component.has_value()) {
                    auto text = std::dynamic_pointer_cast<TextComponent>(std::any_cast<std::shared_ptr<IComponent>>(component.value()));
                    if (text) {
                        sortedComponents.push_back(*text);
                    }
                }
            }

            std::sort(sortedComponents.begin(), sortedComponents.end(),
                      [](const TextComponent &a, const TextComponent &b) {
                          return a.getLayer() < b.getLayer();
                      });

            for (const auto &component: sortedComponents) {
                renderEngine->Draw(component);
            }
        };

        auto sortAndDrawSprite = [this](std::vector<std::optional<std::shared_ptr<IComponent>>> &components) {
            std::vector<SpriteComponent> sortedComponents;

            for (const auto &component: components) {
                if (component.has_value()) {
                    auto sprite = std::dynamic_pointer_cast<SpriteComponent>(std::any_cast<std::shared_ptr<AComponent>>(component.value()));
                    if (sprite) {
                        sortedComponents.push_back(*sprite);
                    }
                }
            }

            std::sort(sortedComponents.begin(), sortedComponents.end(),
                      [](const SpriteComponent &a, const SpriteComponent &b) {
                          return a.getLayer() < b.getLayer();
                      });

            for (const auto &component: sortedComponents) {
                renderEngine->Draw(component);
            }
        };

        auto sortAndDrawParallax = [this](std::vector<std::optional<std::shared_ptr<IComponent>>> &components) {
            std::vector<ParallaxComponent> sortedComponents;

            for (const auto &component: components) {
                if (component.has_value()) {
                    auto parallax = std::dynamic_pointer_cast<ParallaxComponent>(std::any_cast<std::shared_ptr<AComponent>>(component.value()));
                    if (parallax) {
                        sortedComponents.push_back(*parallax);
                    }
                }
            }

            std::sort(sortedComponents.begin(), sortedComponents.end(),
                      [](const ParallaxComponent &a, const ParallaxComponent &b) {
                          return a.getLayer() < b.getLayer();
                      });

            for (auto &component: sortedComponents) {
                renderEngine->Draw(component);
            }
        };

        sortAndDrawText(textComponents);
        sortAndDrawSprite(spriteComponents);
        sortAndDrawParallax(parallaxComponents);
    }



}
