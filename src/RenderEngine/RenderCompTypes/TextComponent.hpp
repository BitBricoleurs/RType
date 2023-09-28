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
        TextComponent(const std::string& text, Vect2 pos, int fontSize, size_t layer, Color color) {
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
        Color getColor() const { return color;}
        void setColor(Color color) { this->color = color; }
        Vect2 getPos() const { return pos; }
        void setPos(Vect2 pos) { this->pos = pos; }

    private:
        size_t layer;
        std::string text;
        Vect2 pos;
        int fontSize;
        Color color;
    };
}
