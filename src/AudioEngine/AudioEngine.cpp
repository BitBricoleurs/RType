/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngine
*/

#include "AudioEngine.hpp"
#include <stdexcept>

namespace GameEngine {

    AudioEngine::AudioEngine() {
        InitAudioDevice();
    }

    AudioEngine::~AudioEngine() {
        CloseAudioDevice();
    }

    void AudioEngine::PlaySound(const AudioComponent& audioComponent) {
        if (soundMap.find(audioComponent.audioPath) == soundMap.end()) {
            soundMap[audioComponent.audioPath] = LoadSound(audioComponent.audioPath.c_str());
        }

        if (!IsAudioDeviceReady()) {
            throw std::runtime_error("Audio device not ready");
        }

        ::PlaySound(soundMap[audioComponent.audioPath]);
    }

    void AudioEngine::StopSound(const AudioComponent& audioComponent) {
        if (soundMap.find(audioComponent.audioPath) != soundMap.end()) {
            ::StopSound(soundMap[audioComponent.audioPath]);
        }
    }
}
