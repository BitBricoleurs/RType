//
// Created by Bartosz on 10/23/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "LoadConfig.hpp"
#include "WindowInfoComponent.hpp"


namespace RenderEngine {
    class RenderEngineCinematicSystem : public GameEngine::ISystem {
    public:
        RenderEngineCinematicSystem() = default;
        ~RenderEngineCinematicSystem() = default;

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) override;

    private:
        std::string jsonPath;
        std::string nextScene;
        bool isPlaying;
        float clock;
        bool isPaused = false;
        float clockNonPausable;
        float CinematicDuration;

        void loadJSON(const std::string& path, GameEngine::ComponentsContainer& componentsContainer);
        void playCinematic(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler);
        void endCinematic();

        float Lerp(float start, float end, float progress) {
            return start + progress * (end - start);
        }
    };
}

