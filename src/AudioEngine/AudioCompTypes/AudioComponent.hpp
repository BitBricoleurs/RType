/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioComponent
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <string>

namespace GameEngine {
    class AudioComponent : public AComponent {
    public:
        AudioComponent(const std::string& audioPath) {
            this->audioPath = audioPath;
        }
        ~AudioComponent() = default;

        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("Player");
          }
        std::string audioPath;
        int audioTimer;
        int volume;
    private:
    };
}
