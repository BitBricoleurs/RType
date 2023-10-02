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
        TextComponent(const std::string& text, Vector2 pos, int fontSize, size_t layer, ColorR color) {
            this->text = text;
            this->fontSize = fontSize;
            this->layer = layer;
            this->color = color;
            this->pos = pos;
        }
        ~TextComponent() = default;

        std::string getText() const { return text; }
        void setText(const std::string& text) { this->text = text; }
        int getFontSize() const { return fontSize; }
        void setFontSize(int fontSize) { this->fontSize = fontSize; }
        int getLayer() const { return layer; }
        void setLayer(int layer) { this->layer = layer; }
        ColorR getColor() const { return color;}
        void setColor(ColorR color) { this->color = color; }
        Vector2 getPos() const { return pos; }
        void setPos(Vector2 pos) { this->pos = pos; }
        size_t getComponentType() override { return ComponentsType::getNewComponentType("TextComponent"); }

    private:
        size_t layer;
        std::string text;
        Vector2 pos;
        int fontSize;
        ColorR color;
    };
}
