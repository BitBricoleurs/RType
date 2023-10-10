/*
** EPITECH PROJECT, 2023
** RType
** File description:
** TextComponent
*/

#pragma once

#include "AComponent.hpp"
#include <string>
#include "Utils.hpp"
#include "raylib.h"
#include "ComponentsType.hpp"

namespace GameEngine {
    class TextComponent : public AComponent {
    public:
        TextComponent(const std::string& text, Vect2 pos, int fontSize, size_t layer, ColorR color) {
            this->text = text;
            this->fontSize = fontSize;
            this->layer = layer;
            this->color = color;
            this->pos = pos;
        }
        ~TextComponent() override = default;

        size_t layer;
        std::string text;
        Vect2 pos;
        int fontSize;
        ColorR color{};
        bool isVisible = true;

    private:
    };
}
