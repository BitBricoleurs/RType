/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngineSystem
*/

// RenderEngineSystem.hpp
#pragma once

#include "ISystem.hpp"
#include "../RenderEngine/RenderCompTypes/TextComponent.hpp"
#include "../RenderEngine/RenderCompTypes/SpriteComponent.hpp"
#include "../RenderEngine/RenderCompTypes/ParallaxComponent.hpp"
#include "RenderEngine.hpp"
#include "ComponentsType.hpp"
#include <memory>

namespace GameEngine {
    class RenderEngineSystem : public ISystem {
    public:
        RenderEngineSystem( int screenWidth, int screenHeight, const char* windowTitle);
        ~RenderEngineSystem();

        virtual void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override;

    private:
        std::shared_ptr<RenderEngine> renderEngine;
    };
}
