/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngine
*/

#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>
#include "AudioCompTypes/AudioComponent.hpp"

namespace GameEngine {
    class AudioEngine {
    public:
        AudioEngine();
        ~AudioEngine();

        void Initialize();
        void PlaySound(const AudioComponent& audioComponent);
        void StopSound(const AudioComponent& audioComponent);
    private:
        std::unordered_map<std::string, Sound> soundMap;

    };
}
