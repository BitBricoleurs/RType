/*
** EPITECH PROJECT, 2023
** RType
** File description:
** TextComponent
*/

#pragma once

#include "AComponent.hpp"
#include <string>
#include "Vect2.hpp"
#include "raylib.h"
#include "ColorR.hpp"
#include "ComponentsType.hpp"

namespace RenderEngine {
    class TextComponent : public GameEngine::AComponent {
    public:
        TextComponent(const std::string& text, Utils::Vect2 pos, int fontSize, size_t layer, Utils::ColorR color) {
            this->text = text;
            this->fontSize = fontSize;
            this->layer = layer;
            this->color = color;
            this->pos = pos;
        }
        ~TextComponent() override = default;
        size_t getComponentType() override { return GameEngine::ComponentsType::getNewComponentType("TextComponent"); }

        size_t layer;
        std::string text;
        Utils::Vect2 pos;
        int fontSize;
        Utils::ColorR color{};
        bool isVisible = true;

    private:
    };
}
