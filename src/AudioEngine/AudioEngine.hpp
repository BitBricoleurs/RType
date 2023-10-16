#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>
#include "AudioComponent.hpp"
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#endif

namespace GameEngine {
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
