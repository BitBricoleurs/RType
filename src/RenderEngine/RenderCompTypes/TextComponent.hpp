/*
** EPITECH PROJECT, 2023
** RType
** File description:
** TextComponent
*/

#pragma once

#include "../../GameEngine/Components/AComponent.hpp"
#include <string>

namespace GameEngine {
    class TextComponent : public AComponent {
    public:
        TextComponent(const std::string& text, int x, int y, int fontSize) {
            this->text = text;
            this->x = x;
            this->y = y;
            this->fontSize = fontSize;
        }
        ~TextComponent() = default;

        std::string getText() const { return text; }
        void setText(const std::string& text) { this->text = text; }
        int getX() const { return x; }
        void setX(int x) { this->x = x; }
        int getY() const { return y; }
        void setY(int y) { this->y = y; }
        int getFontSize() const { return fontSize; }
        void setFontSize(int fontSize) { this->fontSize = fontSize; }
        int getLayer() const { return layer; }
        void setLayer(int layer) { this->layer = layer; }

    private:
        size_t layer;
        std::string text;
        int x, y;
        int fontSize;
    };
}
