/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngineSystem
*/

// RenderEngineSystem.hpp
#pragma once

#include "../Core/ISystem.hpp"
#include "../RenderEngine/RenderCompTypes/TextComponent.hpp"
#include "../RenderEngine/RenderCompTypes/SpriteComponent.hpp"
#include "../RenderEngine/RenderCompTypes/ParallaxComponent.hpp"
#include "../RenderEngine/RenderEngine.hpp"
#include "../Components/ComponentsType.hpp"
#include <memory>

namespace GameEngine {
    class RenderEngineSystem : public ISystem {
    public:
        RenderEngineSystem( int screenWidth, int screenHeight, const char* windowTitle);
        ~RenderEngineSystem();

        void update(std::unordered_map<size_t, std::vector<std::optional<std::any>>> componentsContainer, 
                    std::shared_ptr<EventHandler> eventHandler) override;

    private:
        std::shared_ptr<RenderEngine> renderEngine;
    };
}
