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
#include "GameEngine.hpp"
#include <memory>
#include "ResourceManager.hpp"
#include "LoadConfig.hpp"
#include "ConfigData.hpp"

namespace RenderEngine {
    class RenderEngineSystem : public GameEngine::ISystem {
    public:
        explicit RenderEngineSystem(const char* windowTitle, GameEngine::GameEngine& componentContainer);
        ~RenderEngineSystem();

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) override;

        void PreloadSceneAssets(const std::vector<std::string>& assetList);
        void UnloadAssets(const std::vector<std::string>& assetList);
        void UnloadAssets();
        void LoadAssetsFromJSON(const std::string path);

        size_t getScreenHeight();
        size_t getScreenWidth();
    private:
        std::unique_ptr<RenderEngine> renderEngine;
        std::shared_ptr<ResourceManager> resourceManager;
};
}
