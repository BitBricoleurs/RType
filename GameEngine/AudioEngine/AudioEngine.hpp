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

namespace GameEngine {
    class AudioEngine {
    public:
        AudioEngine();
        ~AudioEngine();

        void Initialize();
        void PlaySound(const std::string &key, const std::string &soundFile);
        void StopSound(const std::string &key);
    private:
        std::unordered_map<std::string, Sound> soundMap;

    };
}
