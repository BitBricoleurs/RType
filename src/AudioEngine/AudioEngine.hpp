#pragma once

#include "LoadConfig.hpp"
#include "raylib.h"
#include <string>
#include <unordered_map>
#include "AudioComponent.hpp"

namespace AudioEngine {
    class AudioEngine {
    public:
        AudioEngine();
        ~AudioEngine();

        void Play(const AudioComponent& audioComponent);
        void Stop(const AudioComponent& audioComponent);
        void ChangeVolume(const AudioComponent& audioComponent, int volume);
        void Update();
    private:
        std::unordered_map<std::string, Sound> soundMap;
        std::unordered_map<std::string, Music> musicMap;

        bool isLongAudio(const AudioComponent& audioComponent);
    };
}
