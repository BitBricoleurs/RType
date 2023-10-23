//
// Created by Bartosz on 10/23/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"


namespace RenderEngine {
    class RenderEngineCinematicSystem : public GameEngine::ISystem {
    public:
        RenderEngineCinematicSystem();
        ~RenderEngineCinematicSystem() = default;

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) override;

    private:
        std::string jsonPath;
        std::string nextScene;
        bool isPlaying;
        float clock;

        void loadJSON(const std::string& path, GameEngine::ComponentsContainer& componentsContainer);
        void playCinematic(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler);
        void endCinematic();
    };
}

