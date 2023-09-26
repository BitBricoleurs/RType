/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngineSystem
*/

#pragma once

#include "../GameEngine/Core/ISystem.hpp"
#include "../AudioEngine/AudioEngine.hpp"
#include "../AudioEngine/AudioCompTypes/AudioComponent.hpp"
#include "../GameEngine/Components/ComponentsType.hpp"
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
        std::shared_ptr<AudioEngine> audioEngine;
    };
}
