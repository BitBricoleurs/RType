/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngineSystem
*/

#pragma once

#include "../ISystem.hpp"
#include "../AudioEngine/AudioEngine.hpp"
#include "../AudioEngine/AudioCompTypes/AudioComponent.hpp"
#include "../ComponentsType.hpp"
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

        void update(std::unordered_map<size_t, std::vector<std::optional<std::any>>> componentsContainer,
                    std::shared_ptr<EventHandler> eventHandler) override;

    private:
        std::shared_ptr<AudioEngine> audioEngine;
    };
}
