/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngine
*/

#include "AudioEngine.hpp"

#include "AudioEngine.hpp"
#include <stdexcept>

namespace GameEngine {

    AudioEngine::AudioEngine() {
        InitAudioDevice();
    }

    AudioEngine::~AudioEngine() {
        CloseAudioDevice();
    }

    void AudioEngine::PlaySound(const std::string &key, const std::string &soundFile) {
        if (soundMap.find(key) == soundMap.end()) {
            soundMap[key] = LoadSound(soundFile.c_str());
        }

        if (!IsAudioDeviceReady()) {
            throw std::runtime_error("Audio device not ready");
        }

        ::PlaySound(soundMap[key]);
    }

    void AudioEngine::StopSound(const std::string &key) {
        if (soundMap.find(key) != soundMap.end()) {
            ::StopSound(soundMap[key]);
        }
    }
}
