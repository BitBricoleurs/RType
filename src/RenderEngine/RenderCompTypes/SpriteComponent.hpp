/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpriteComponent
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Vect2.hpp"
#include "ColorR.hpp"
#include "rect.hpp"
#include <string>

namespace RenderEngine {
    class SpriteComponent : public GameEngine::AComponent {
    public:
        SpriteComponent(const std::string& imagePath, Utils::Vect2 pos, Utils::rect rect1, size_t layer, float scale, float rotation, Utils::ColorR tint) {
            this->imagePath = imagePath;
            this->pos = pos;
            this->rect1 = rect1;
            this->layer = layer;
            this->rotation = rotation;
            this->scale = scale;
            this->tint = tint;
            this->flash = false;
            this->origin = Utils::Vect2(0.0f,0.0f);
        }
        ~SpriteComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("SpriteComponent");
        }

        Utils::Vect2 pos;
        Utils::rect rect1;
        float scale;
        float rotation;
        size_t layer;
        std::string imagePath;
        Utils::Vect2 origin;
        Utils::ColorR tint;
        bool isVisible = true;
        bool flash = false;
    private:
    };
}
