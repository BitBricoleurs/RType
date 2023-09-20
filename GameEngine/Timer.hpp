//
// Created by Theophilus Homawoo on 20/09/2023.
//

#pragma once

#include <chrono>

namespace GameEngine {
    class Timer {
    public:
        Timer() : start_time_point(std::chrono::high_resolution_clock::now()) {}

        void start() {
            start_time_point = std::chrono::high_resolution_clock::now();
        }

        double elapsedMilliseconds() const {
            return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start_time_point).count();
        }

        double elapsedSeconds() const {
            return elapsedMilliseconds() / 1000.0;
        }

        void reset() {
            start();
        }

    private:
        std::chrono::high_resolution_clock::time_point start_time_point;
    };
} // namespace GameEngine
