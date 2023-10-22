/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngineSystem
*/

#pragma once

#include "ISystem.hpp"
#include "AudioEngine.hpp"
#include "AudioComponent.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <optional>
#include <any>

namespace GameEngine {
    class AudioEngineSystem : public ISystem {
    public:
        AudioEngineSystem();
        ~AudioEngineSystem();

        virtual void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override;

    private:
        std::shared_ptr<AudioEngine::AudioEngine> audioEngine;
    };
}
