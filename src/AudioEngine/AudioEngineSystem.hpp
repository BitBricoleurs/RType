/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngineSystem
*/

#pragma once

#include "ISystem.hpp"
#include "AudioComponent.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <optional>
#include <any>

namespace AudioEngine {
    class AudioEngine;
    class AudioEngineSystem : public GameEngine::ISystem {
    public:
        AudioEngineSystem();
        ~AudioEngineSystem();

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override;

    private:
        std::shared_ptr<AudioEngine> audioEngine;
    };
}
