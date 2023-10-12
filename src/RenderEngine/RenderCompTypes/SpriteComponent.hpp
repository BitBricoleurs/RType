/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpriteComponent
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Utils.hpp"
#include <string>

namespace GameEngine {
    class SpriteComponent : public AComponent {
    public:
        SpriteComponent(const std::string& imagePath, Vect2 pos, rect rect1, size_t layer, float scale, float rotation, ColorR tint) {
            this->imagePath = imagePath;
            this->pos = pos;
            this->rect1 = rect1;
            this->layer = layer;
            this->rotation = rotation;
            this->scale = scale;
            this->tint = tint;
            this->origin = Vect2(0.0f,0.0f);
            this->flash = false;
        }
        ~SpriteComponent() = default;

        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("SpriteComponent");
        }

        Vect2 pos;
        rect rect1;
        float scale;
        float rotation;
        size_t layer;
        std::string imagePath;
        Vect2 origin;
        ColorR tint;
        bool flash;
        bool isVisible = true;
    private:
    };
}

