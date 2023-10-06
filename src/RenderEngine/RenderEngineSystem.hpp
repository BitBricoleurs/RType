/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RenderEngineSystem
*/

#pragma once


#include "ISystem.hpp"
#include "TextComponent.hpp"
#include "SpriteComponent.hpp"
#include "RenderEngine.hpp"
#include "ComponentsType.hpp"
#include <memory>
#include "WindowInfoComponent.hpp"

namespace GameEngine {
    class RenderEngineSystem : public ISystem {
    public:
        RenderEngineSystem(const char* windowTitle);
        ~RenderEngineSystem();

        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override;

        size_t getScreenHeight();
        size_t getScreenWidth();
    private:
        std::unique_ptr<RenderEngine> renderEngine;
};
}
