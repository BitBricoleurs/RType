/*
** EPITECH PROJECT, 2023
** RType
** File description:
** TextComponent
*/

#pragma once

#include "../../AComponent.hpp"
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
        ~TextComponent();

        std::string getText() const { return text; }
        void setText(const std::string& text) { this->text = text; }
        int getX() const { return x; }
        void setX(int x) { this->x = x; }
        int getY() const { return y; }
        void setY(int y) { this->y = y; }
        int getFontSize() const { return fontSize; }
        void setFontSize(int fontSize) { this->fontSize = fontSize; }

    private:
        std::string text;
        int x, y;
        int fontSize;
    };
}
