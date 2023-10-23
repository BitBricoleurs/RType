/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngineSystem
*/

#pragma once

#include "ComponentsType.hpp"
#include "IComponent.hpp"
#include "ISystem.hpp"
#include "RenderEngine.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "WindowInfoComponent.hpp"
#include <memory>

namespace RenderEngine {
    class RenderEngineSystem : public GameEngine::ISystem {
    public:
        explicit RenderEngineSystem(const char* windowTitle);
        ~RenderEngineSystem();

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) override;

        size_t getScreenHeight();
        size_t getScreenWidth();
    private:
        std::unique_ptr<RenderEngine> renderEngine;
};
}
