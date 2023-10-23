//
// Created by Theophilus Homawoo on 17/10/2023.
//

#pragma once

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#endif
#include <string>
#include <unordered_map>
#include "AudioComponent.hpp"
#include "Vect3.hpp"
#include "al.h"
#include "alc.h"

namespace AudioEngine {
    class AudioEngine {
    public:
        AudioEngine();
        ~AudioEngine();

        void Play(const AudioComponent& audioComponent);
        void Play(const AudioComponent& audioComponent, const Utils::Vect3& soundPos, const Utils::Vect3& listenerPos);
        void Stop(const AudioComponent& audioComponent);
        void Update();

    private:
        ALCdevice* device;
        ALCcontext* context;
        std::unordered_map<std::string, ALuint> soundBuffers;
        std::unordered_map<std::string, ALuint> soundSources;
    };
}

