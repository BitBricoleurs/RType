/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngineSystem
*/

// RenderEngineSystem.hpp
#pragma once


#include "ISystem.hpp"
#include "TextComponent.hpp"
#include "SpriteComponent.hpp"
#include "RenderEngine.hpp"
#include "ComponentsType.hpp"
#include <memory>

namespace GameEngine {
    class RenderEngineSystem : public ISystem {
    public:
        RenderEngineSystem( int screenWidth, int screenHeight, const char* windowTitle, int numberFps);
        ~RenderEngineSystem();

        virtual void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override;

    private:
        std::shared_ptr<RenderEngine> renderEngine;
    };

    size_t& spriteComponentType();
    size_t& textComponentType();
    size_t& audioComponentType();

}
