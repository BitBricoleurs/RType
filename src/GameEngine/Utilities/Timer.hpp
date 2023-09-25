//
// Created by Theophilus Homawoo on 20/09/2023.
//

#pragma once

#include <chrono>

namespace GameEngine {
    class Timer {
    public:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;

        Timer() : startTime(Clock::now()) {}

        void reset() {
            startTime = Clock::now();
        }

        double elapsedSeconds() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - startTime).count() / 1000.0;
        }
    private:
        TimePoint startTime;
    };

} // namespace GameEngine
