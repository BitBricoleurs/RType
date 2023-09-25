/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngingeSystem
*/

#include "RenderEngineSystem.hpp"

namespace GameEngine {

    RenderEngineSystem::RenderEngineSystem(int width, int height, const char* windowName) {
        renderEngine = std::make_shared<RenderEngine>();
        renderEngine->Initialize(width, height, windowName);
    }

    RenderEngineSystem::~RenderEngineSystem() {
        renderEngine->Shutdown();
    }

    void RenderEngineSystem::update(std::unordered_map<size_t, std::vector<std::optional<std::any>>> componentsContainer,
                                std::shared_ptr<EventHandler> eventHandler) {
    size_t textComponentTypeId = ComponentsType::getComponentType("TextComponent");
    size_t spriteComponentTypeId = ComponentsType::getComponentType("SpriteComponent");
    size_t parallaxComponentTypeId = ComponentsType::getComponentType("ParallaxComponent");
    renderEngine->PollEvents(*eventHandler);

    auto textComponents = componentsContainer[textComponentTypeId];
    auto spriteComponents = componentsContainer[spriteComponentTypeId];
    auto parallaxComponents = componentsContainer[parallaxComponentTypeId];
    for (const auto& component : textComponents) {
        if (component.has_value()) {
            auto text = std::any_cast<std::shared_ptr<AComponent>>(component.value());
            renderEngine->Draw(dynamic_cast<TextComponent&>(*text));
        }
    }


    for (const auto& component : spriteComponents) {
        if (component.has_value()) {
            auto sprite = std::any_cast<std::shared_ptr<AComponent>>(component.value());
            renderEngine->Draw(dynamic_cast<SpriteComponent&>(*sprite));
        }
    }
    for (const auto& component : parallaxComponents) {
        if (component.has_value()) {
            auto parallax = std::any_cast<std::shared_ptr<AComponent>>(component.value());
            renderEngine->Draw(dynamic_cast<ParallaxComponent&>(*parallax));
        }
    }
}

}
